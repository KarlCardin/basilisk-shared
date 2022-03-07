coord interface_normal (Point point, scalar c);
#define interface_normal(point, c) interface_normal (point, c)

attribute {
 vector solid_norm;
}

#if MASK
attribute {
 scalar contact;
}
#endif

#define LEVEL 7
#define Bond 1
#define Gravity 0
#define RHO 1

#include "grid/quadtree.h"
#include "embed.h"
#include "axi.h"
#include "navier-stokes/centered.h" 
#if NOMASK
#include "solid_height.h"
#endif
#include "contact.h"
#include "vof.h"




#include "two-phase.h"
#include "tension.h" 
/*#include "tag.h"*/
#include "view.h"
#include "output.h"
#include "karl_utilities.h"




double Re = 2000.;
double Ca = .01;
FILE * fp76;
bid wall;
char img_nm[99];
scalar zeroo[];
/*scalar f[], * interfaces = {f};*/
scalar csv[], filled[], contact[];
face vector fsv[];
vector h[],hs[], norm_solid[];
face vector muc1[],muc2[];



u.n[left] = dirichlet(1);
u.t[left] = dirichlet(0);
p[left]   = neumann(0);

u.n[top] = neumann(0);
p[top]   = dirichlet(0);
pf[top]  = dirichlet(0);

#if NOMASK
u.n[embed] = dirichlet(0.);
u.t[embed] = dirichlet(0.);
/*f[embed] = 0.;*/
#endif

#if MASK
u.n[wall] = dirichlet(0.);
u.t[wall] = dirichlet(0.);
h.t[wall] = contact_angle (120*pi/180.);
#endif 


int main() {
  cs = csv;
  fs = fsv;
  size (2.6);
  init_grid (1 << LEVEL);
  rho1 = 1., rho2 = .001;
  mu1 = .1, mu2 = SEPS;  
  f.sigma = 2.;
  f.height = h; 
  f.solid_norm = norm_solid;
  f.contact = contact;
  cs.height = hs;
  foreach()
  zeroo[] = 0.;
  char logname[99];
  sprintf (logname, "Force");
  fp76 = fopen (logname, "w");
  run();
}


event init (t = 0) {
  fraction (f, - sq(x - .2)/.2 - sq(y) + sq(0.5));
  vertex scalar phi[];  
#if NOMASK
  foreach_vertex(){
     phi[] = -(sq(x-50.1828125 ) + sq(y) - sq(50.));
     /*phi[] = -(- sq(x - 0.6) - sq(y) + sq(0.5));*/
     /*phi[] = x-.19;*/
    }
#endif
#if MASK
  foreach_vertex(){
     phi[] =  1.;
    }
  mask (x < .18282 ? wall : none);
#endif
  fractions (phi, csv, fsv);
  boundary({f,csv,cs,fs});
  
  /*foreach()
    u.x[] = - f[];*/
  foreach(){
    if(cs[]<1e-2 && cs[1]>0 && cs[1]<1.)
    		cs[]=0.;
  }
  foreach(){
    /*if(cs[] < 1e-2)
    		cs[]=0.;*/
    if(cs[] == 0.){
    f[]=0.;
    }
  }
  heights(cs,hs);
  
}

/**
=====================
========================
Loop
========================
=====================
*/

/**
=====================
vof
=====================
*/


/**
=====================
Properties 1 of 2
=====================
*/


/**
=====================
advection_term
=====================
*/

/**
=====================
viscous_term
=====================
*/

/**
=====================
Acceleratrion
=====================
*/
event acceleration (i++){
/*cstats ss = curvature(f);
  	fprintf (stderr, "cstats: %i %i %i %i\n",
    		ss.h, ss.f, ss.a, ss.c);*/
    	}


/**
=====================
Adapt
=====================
*/

event adapt(i++){
     /*double sb = statsf(f).sum;*/
     scalar magcs[];
     foreach()
     	magcs[]=noise()*(1.-cs[]);
     	/*cs fills small portion of cell, 1/cs*/
     	/*magcs[]= 1/(cs[]+SEPS);*/
     boundary({magcs});
     
     
	adapt_wavelet ({magcs,cs,f},(double[]){0.0005,0.0005}, LEVEL, minlevel = 4);
	/*double sa = statsf(f).sum;*/
	/*assert (fabs(sa - sb) < 2e-6);*/
	}


/**
=====================
Properties 2 of 2
=====================
*/





event end (i = 1000){ 
     fclose (fp76);
     }     



/**
=====================
Ouputs
=====================
*/
#if 0
event droplets (i += 1)
{
  scalar m[];
  foreach()
    m[] = f[] > 1e-3;
  int n = tag (m);

  /**
  Once each cell is tagged with a unique droplet index, we can easily
  compute the volume *v* and position *b* of each droplet. Note that
  we use *foreach_leaf()* rather than *foreach()* to avoid doing a
  parallel traversal when using OpenMP. This is because we don't have
  reduction operations for the *v* and *b* arrays (yet). */

  double v[n];
  coord b[n];
  for (int j = 0; j < n; j++)
    v[j] = b[j].x = b[j].y = b[j].z = 0.;
  foreach_leaf()
    if (m[] > 0) {
      int j = m[] - 1;
      v[j] += dv()*f[];
      coord p = {x,y,z};
      foreach_dimension()
	b[j].x += dv()*f[]*p.x;
    }

 /**
 When using MPI we need to perform a global reduction to get the
 volumes and positions of droplets which span multiple processes. */

#if _MPI
  MPI_Allreduce (MPI_IN_PLACE, v, n, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
  MPI_Allreduce (MPI_IN_PLACE, b, 3*n, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
#endif

  /**
  Finally we output the volume and position of each droplet to
  standard output. */

  for (int j = 0; j < n; j++)
    fprintf (fout, "drooooops %d %g %d %g %g %g\n", i, t,
	     j, v[j], b[j].x/v[j], b[j].y/v[j]);
  fflush (fout);
}

#endif
#if 1
event output (i+=10){
  	FILE * fp2 = fopen ("output_facet_sol","w");
  	output_facets (cs, fp2);
  	fclose (fp2);
  
  	FILE * fp3 = fopen ("output_facet_liq","w");
  	output_facets (f ,fp3);
  	fclose (fp3);
     

     /* This somehow messed it up....
     scalar f_filt;
     foreach(){
     	f_filt[] = nodata;
     	if (cs[]>0. && cs[]<1.)
     		f_filt[]=f[];
     }
     */
  	FILE * fp33 = fopen ("f","w");
  	output_scal(f,fp33);
  	fclose (fp33);
     
  	
  	
  	FILE * fp7 = fopen ("output_cells","w");
  	output_cells (fp7);
  	fclose (fp7);
  	
  	/*contact_iden(f, f.contact , cs);*/
  	FILE * fp44 = fopen ("contact","w");
     output_scal(contact,fp44);
     fclose (fp44);


}
#endif

#if 1
event output (i+=10){
  char str[99];
  view(fov = 10, width = 1080, height = 1080,tx = -.25, ty = -0.15);
  vector h_sol[];
  #if 1
  foreach(){
     h_sol.x[]=nodata;
     h_sol.y[]=nodata;
     if(contact[1]==2.){ /* */
         h_sol.x[]=0.;
         h_sol.y[]=h.y[];
         /*h_sol.y[]=h.y[]*Delta;
         fprintf (stderr, "vectors %0.3g \n",h.y[]*Delta);*/
         
         }
   }
   hits ("h_sol",lc = {1, 0, 1}, lw = 2);  
  draw_vof("cs","zeroo");
  draw_vof("cs","zeroo", filled = -1, fc = {0.3, 0.3, 0.3});
  squares("f", min = 0., max = 1., map = cool_warm);
  squares("contact", min = 1., max = 2., map = cool_warm);
  
  draw_vof("f","zeroo");
  draw_vof("f","zeroo", filled = 1, fc = {0.7, 0.7, 0.7});
  fprintf (stderr, "liq done \n");
  
  
  sprintf (str, "%i", i);
  draw_string (str, size = 30);
  cells();
  sprintf (img_nm, "out_%i.png", i);
  save(img_nm);
  #endif
  
  
}		 
#endif


#if 1
event logfile (i++,i>2) {
  static double sfmin = HUGE, sfmax = -HUGE;
  double s = statsf(f).sum;
  if (s < sfmin) sfmin = s;
  if (s > sfmax) sfmax = s;
  double e = 2.*(sfmax - sfmin)/(sfmax + sfmin);
  fprintf (ferr, "i: %i V liq: %.12f  error liq:%.12f \n", i, s, e);
  fflush (ferr);
  /*assert (e < 4e-8);*/
  /*assert (e1 < 5e-5);*/
}
#endif
