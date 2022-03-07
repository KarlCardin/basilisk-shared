set size ratio -1
set key off
plot 'output_cells' w l \
     , 'output_facet_sol' w lines lw 3 \
     ,'neigh' u 1:2:3  w labels
     #,'output_center' u 1:2 
	#,'output_cs1' u 1:2:(sprintf("csa :%0.3f", $3)) w labels \
     #,'output_ycord' u 1:2:(sprintf("y:%0.3f", $3)) w labels offset 0,1,0 \
     #,'output_fmx' u 1:2:(sprintf("fmx:%0.3f", $3)) w labels offset 0,2,0 \
     #,'output_cs2' u 1:2:(sprintf("csb :%0.3f", $3)) w labels offset 0,-1,0 \
     #,'output_cm1' u 1:2:(sprintf("cma :%0.3f", $3)) w labels offset 0,-2,0 \
     #,'output_cm2' u 1:2:(sprintf("cmb :%0.3f", $3)) w labels offset 0,-3,0 \
     #,'output_fsy' u 1:2:(sprintf("fsy :%0.3f", $3)) w labels offset 0,-4,0 \
     #,'output_fsx' u 1:2:(sprintf("fsx :%0.3f", $3)) w labels offset 0,-5,0 \
    
     
   
pause mouse close 

# 'output_cs' u 1:2:3 w labels font ",6"
# , 'output_facet_liq_adjusted' w lines lw 3 
#     ,'log' u 1:2:3 w labels font ",6"
# , 'heights' u 1:2:3 w labels font ",6"\
 #   , 'heights_adjusted' u 1:2:3 w labels font ",6" tc lt 2 offset 0,1,0\
 # ,'output_f' u 1:2:3 w labels font ",6"
 # ,'log' u 1:2:3 w labels 
  #   , 'output_cs_prevof' u 1:2:3 w labels font ",6" tc lt 2 offset 0,1,0\
  #  , 'output_cs' u 1:2:3 w labels font ",6"
  #   ,'log' u 1:2:3:4:5 w vector lc rgb variable
  #, 'output_fs' u 1:2:3 w labels\
    #, 'output_fm' u 1:2:3 w labels tc lt 2 offset 0,1,0
    # ,'log' u 1:2:3 w labels 
    #, 'contact' u 1:2:3 w labels tc lt 2 offset 0,1,0
    # \
    #,'f'  u 1:2:3 w labels tc lt 2 offset 0,1,0  \
    #,'f'  u 1:2:3 w labels tc lt 2 offset 0,1,0 
    #, "<awk '$1 ~ /^ *centroid/' vec" u 2:3:4 w labels tc lt 3 offset 0,2,0
    #,'f'  u 1:2:3 w labels tc lt 2 offset 0,1,0\
    
    #    , 'output_facet_sol' w lines lw 3 \
