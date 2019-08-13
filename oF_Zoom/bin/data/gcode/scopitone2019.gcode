$X
$N1=F6000
M05 S150

G90
G21

; go to smoke mudule
M03 S150
G1 F6000
G1  X2000 Y1000
; stay at smoke module
M03 S500
G4 P60

; go to water pump module
G4 P0
M03 S150
G1 F6000
G1  X2700 Y2500
; stay at water pump module
M03 S400
G4 P60

; go to tape module
G4 P0
M03 S150
G1 F6000
G1  X2300 Y3300
; go to tape module end
M03 S350
G1 F1000
G1  X1500 Y3100

; go to amplification module
G4 P0
M03 S150
G4 P0
G1 F6000
G1  X1200 Y2400
; stay at amplification module
M03 S500
G4 P60

; go to CD module
G4 P0
M03 S150
G1 F6000
G1  X700 Y1500
; stay at CD module
M03 S400
G4 P60

; go to bottle module
M03 S150
G1 F6000
G1  X500 Y3200
; stay at bottle module
M03 S700
G4 P60

; go to semi-home position
G4 P0
M03 S150
G1 F6000
G1 X300 Y300

; homing
G4 P0
M05 S0
$H
