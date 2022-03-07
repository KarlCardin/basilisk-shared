attribute {
 scalar contact;
}

#if 0
static void contact_iden (scalar c, scalar con, scalar cs)
{ 
  bool adjacent_to_empty;
  bool adjacent_to_solid;
  foreach(){
  adjacent_to_empty =false;
  adjacent_to_solid =false;
  if (c[] > 1e-6) {
    for (int i = -1; i <= 1; i += 2)
      foreach_dimension(){
	   if (c[i] < 1e-6 && cs[i] > 0) /* zero fluid and not completely solid */
	  	adjacent_to_empty = true;
	   if (cs[i] == 0.)
	  	adjacent_to_solid = true; /* completely solid cell*/
	  }
  }
  if (adjacent_to_solid && adjacent_to_empty)
     con[] = 2.;
  else if (adjacent_to_solid)
     con[] = 1.;
  else 
  	con[] = nodata; 
  }   
}
#endif


static void contact_iden (scalar c, scalar con, scalar cs)
{ 
  bool adjacent_to_empty;
  bool adjacent_to_solid;
  foreach(){
  adjacent_to_empty =false;
  adjacent_to_solid =false;
  if (c[] > 1e-6 && cs[] < 1.) {
   #if 0
   for (int i = -1; i <= 1; i += 2)
      foreach_dimension(){
	   if (c[i] < 1e-6 && cs[i] > 0) /* zero fluid and not completely solid */
	  	adjacent_to_empty = true;
	  }
   #endif
   foreach_neighbor(1){
   	   if (c[] < 1e-6 && cs[] > 0)
	   adjacent_to_empty = true; /* completely solid cell*/
   }
   foreach_neighbor(1){
   	   if (cs[] == 0.)
	   adjacent_to_solid = true; /* completely solid cell*/
   }
  }
  /*if(cs[]<0.1)
  	con[] = 1.;
  else */
  if (adjacent_to_solid && adjacent_to_empty) /*&& c[]<1. && c[]>1e-4*/
     con[] = 2.;
  else if (adjacent_to_solid )/*|| cs[]==0. */
     con[] = 1.;
  else 
  	con[] = nodata; 
  } 
  /*
  foreach(){
  	if(con[-1]==2.)
  		con[]=1.;
  }
  */
}

static void solid_height (scalar f, vector h, scalar cs){
  	vector ns[],hsolid[],hs[];
  	scalar change[];
     scalar contact = f.contact; 
     foreach(){
     		foreach_dimension(){
   				hsolid.x[]= nodata;
   			}
   	}

   	foreach(){
  	     if(cs[]<0.1 && contact[]!=2.){
     		foreach_dimension(){
   				h.x[]= nodata;
   			}
   		}
   	}
   	
   	

  	
  	foreach(){
  		if(contact[1]==2.){
  		     /*fprintf (stderr, "sOLID hEIGHT SOLID_HEIGH.H \n");*/
    			hsolid.y[] = h.y[1]-(.5);/*(orientation(h.x[]) ? 1. : -1.)/tan(90); -(4)*/
    			}
  	}
  	
  	
  	
  	foreach(){
   		foreach_dimension(){	
  			if(h.x[]==nodata && hsolid.x[]!=nodata) /*(allocated(hsolid.x[])) && && h.x[]==nodata*/
  		       h.x[]=hsolid.x[]; 
   			}
  		}

  }


static void fill (scalar f, scalar contact, scalar cs){
	foreach(){
		if(contact[]==1.){
			f[]=1.;
		}	
		/*if(f[]>1-1e-2 && contact[]==1){
			f[]=1.;
		}*/	
	}	
}

static void solid_normal (scalar c, scalar cs){
     scalar contact = c.contact;
     vector solid_norm = c.solid_norm;
	foreach(){
		if(contact[]==2.){
			coord m = interface_normal (point, cs);
			foreach_dimension()
				solid_norm.x[] = m.x;
		}
		else{
		    solid_norm.x[] = nodata;
		    solid_norm.y[] = nodata;
		}	
	}	
}


static void empty (scalar f, scalar contact, scalar cs){
	foreach(){
		if(contact[]==1 && cs[]<0.005){
			f[]=0.;
		}
		if(contact[] == 2 && f[]<1e-6){
			f[]=0.;
		}
			
	}	
}


extern scalar * interfaces;


event init (i = 0) {
  for (scalar c in interfaces)
    if (c.height.x.i){
      contact_iden(c, c.contact , cs); 
      fill (c, c.contact , cs);
      solid_height (c, c.height, cs);
      solid_normal (c, cs);
     }
  
}

event vof (i++) {
  for (scalar c in interfaces)
    if (c.height.x.i){
      /*
      fill(c, c.contact , cs);*/
      contact_iden(c, c.contact , cs);
      solid_height (c, c.height, cs);
      solid_normal (c, cs);
      
     }
    
}

