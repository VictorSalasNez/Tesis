set D; #Conjunto de terminales
set N; #Conjunto de viajes
#set NF dimen 2;
set NF within {N, N}; #Subconjunto de pares de viajes factibles
#set D1 dimen 2;
set D1 within {D,N};
#set D2 dimen 2;
set D2 within {N,D};
#set V{D} within N; #Subconjunto de viajes por terminal
#set A{D}:={NF,N,D};

param K {d in D} >= 0; #Capacidad máxima de un viaje

param Cij {(i,j) in NF} >= 0; #Costo de realizar el viaje i + costo de realiza el viaje j + costo del viaje entre el
									#lugar de destino del viaje i y el lugar de origen del viaje j
param Cid {(i,d) in D2} >= 0; #Costo de realizar el viaje desde el lugar de destino del viaje i hasta el depósito d
param Cdi {(d,i) in D1} >= 0; #Costo de realizar el viaje desde el depósito d hasta el lugar de origen del viaje i


var Xij {(i,j) in NF} binary;
var Xid {(i,d) in D2} binary;
var Xdi {(d,i) in D1} binary;

minimize Z: sum{(d,i) in D1} Cdi[d,i]*Xdi[d,i] + sum{(i,j) in NF} Cij[i,j]*Xij[i,j] + sum{(i,d) in D2} Cid[i,d]*Xid[i,d];

subject to ViajeI{i in N}: sum{j in N:(i,j) in NF} Xij[i,j]+sum{d in D:(i,d) in D2} Xid[i,d] = 1;

subject to Cont{i in N}: sum{j in N:(i,j) in NF} Xij[i,j]+sum{d in D:(i,d) in D2} Xid[i,d] - sum{j in N:(j,i) in NF}Xij[j,i]-sum{d in D:(d,i) in D1}Xdi[d,i]=0;

subject to Cap1{d in D}: sum {i in N:(d,i) in D1} Xdi[d,i] <= K[d];

subject to Cap2{d in D}: sum{i in N:(i,d) in D2} Xid[i,d] <= K[d];