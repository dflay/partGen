#!/bin/bash
sdds2stream -par=Particles -page=1 PSPACE.SDDS > elegantevent.data
sdds2stream -page=1 -col=x,xp,y,yp,p,dt,t PSPACE.SDDS |awk -v OFMT="%.10f" '{print 1,11,0,0,$2*$5*0.511e-3,$4*$5*0.511e-3,sqrt(1.0-$2*$2-$4*$4)*$5*0.511e-3,0.511e-3,$1*1000,$3*1000,0.0,0.0*$7}' >>elegantevent.data
sdds2stream -par=Particles -page=2 PSPACE.SDDS >> elegantevent.data
sdds2stream -page=2 -col=x,xp,y,yp,p,dt,t PSPACE.SDDS |awk -v OFMT="%.10f" '{print 1,11,0,0,$2*$5*0.511e-3,$4*$5*0.511e-3,sqrt(1.0-$2*$2-$4*$4)*$5*0.511e-3,0.511e-3,$1*1000,$3*1000,0.0,0.0*$7}' >>elegantevent.data
#
