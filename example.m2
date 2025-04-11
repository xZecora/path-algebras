restart
needsPackage "AssociativeAlgebras"
kk = ZZ/101
A = kk <| x,y,z |>
f1 = x*x + 3*y*z + 7*z*y
f2 = y*y + 3*z*x + 7*x*z
f3 = z*z + 3*x*y + 7*y*x
I = ideal (f1,f2,f3)
Igb = NCGB(I,5)
