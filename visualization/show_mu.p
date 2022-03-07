set size ratio -1
set key off
plot [0:2.6] [0:2.6] 'output_cells' w l \
    , 'output_facet_sol' w lines lw 3 \
    , 'output_facet_liq' w lines lw 6 \
    ,'mu'  u 1:2:3 w labels\
    , '< tail -n 288 embed_mu'  u 2:3:4 w labels tc lt 2  
    
    
    
    
    
   
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
