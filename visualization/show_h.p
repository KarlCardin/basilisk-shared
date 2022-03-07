set size ratio -1
set key outside
set label "cs=0.0" at -4.8,0 font ",16"
set label "cs=1.0" at 3.5,4 font ",16"
set label "f=1.0" at 0,0 font ",16"
plot [-5:5] [-5:5] 'output_cells' w l \
    , 'output_facet_sol' w lines lw 3 \
    , 'output_facet_liq' w lines lw 6 \
    , 'h_x' u 1:2:3 w labels font ",6" tc lt 2 offset 0,1,0\
    , 'h_y' u 1:2:3 w labels font ",6" \
    , 'h_x_mod' u 1:2:3 w labels font ",6" tc rgb "red" offset 0,-1,0\
    , 'h_y_mod' u 1:2:3 w labels font ",6" tc rgb "red" offset 0,-2,0
    

    
    
    
    
   
pause mouse close 

# 'output_cs' u 1:2:3 w labels font ",6"
# , 'output_facet_liq_adjusted' w lines lw 3 
#     ,'log' u 1:2:3 w labels font ",6"
# , 'heights' u 1:2:3 w labels font ",6"\
 #   , 'heights_adjusted' u 1:2:3 w labels font ",6" tc lt 2 offset 0,1,0\
 # ,'output_f' u 1:2:3 w labels font ",6"
 # ,'log' u 1:2:3 w labels 
