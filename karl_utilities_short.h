struct OutputFlags  {
  FILE * fp;
  coord c;
  double size;
};

void output_flags (struct OutputFlags p)
{
  if (!p.fp) p.fp = stdout;
  foreach(){
  	if (1) { //is_solid_boundary(cell)
  	     //is_boundary(cell)
  	     //cell.flags |= solid_boundary;
  	     //coord n,p;
  		/*n = height_normal (point, f, f.height);*/
  		//n = mycs (point, f);
  		//double alpha = line_alpha  (f[], n);
     	//line_length_center (n, alpha, &p);
     	//printf("%f %f %f %f\n",x+p.x*Delta,y+p.y*Delta, n.x, n.y);}
  		//printf ("%i\n",(cell).flags);
  		//printf ("flag: %i\n",solid_boundary);
     	//printf("%f %f %i\n", x, y,1 << 0| 1<<1 | 1<<3 );
     	fprintf(p.fp,"%f %f %f\n\n", x, y,fm.x[]);
     	//fprintf(p.fp,"%f %f %.1f\n\n", x, y,(cell).flags);
      }
     } 
  fflush (p.fp);
}





/*-------------------------------------------------------*/
/*-------------------------------------------------------*/
/*-------------------------------------------------------*/
struct OutputS  {
  FILE * fp;
  scalar s;
  coord c;
  double size;
};

void output_s (struct OutputS p)
{
  scalar s = p.s;
  if (!p.fp) p.fp = stdout;
  foreach(){
     if (s[] != nodata)
     fprintf(p.fp,"%f %f %.2f\n\n", x, y,s[]);
     /*if (s.x[] >200 s.x[] < 300)
     	fprintf(p.fp,"%f %f %f\n\n", x, y,s.x[]);*/
     } 
  fflush (p.fp);
}

/*-------------------------------------------------------*/
/*-------------------------------------------------------*/
/*-------------------------------------------------------*/
/*-------------------------------------------------------*/
/*
struct OutputMYCS  {
  FILE * fp;
  Point p;
};

void output_mycs (struct OutputMYCS r)
{
  if (!r.fp) r.fp = stdout;
       fprintf(r.fp,"%f %f %f\n", p.x, p.y,0.0);
  fflush (r.fp);
}
*/


struct OutputScal  {
  scalar s;
  FILE * fp;
  coord c;
  double size;
};

void output_scal (struct OutputScal p)
{
  if (!p.fp) p.fp = stdout;
  scalar c = p.s;
  foreach(){
        if (c[] != nodata){
     	fprintf(p.fp,"%0.13f %0.13f %0.13f\n", x, y,c[]);
     	}
      }
  fflush (p.fp);
}




