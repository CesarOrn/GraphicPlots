coeff = h5read("EXAMPLE_DSET.h5","/Coeff");
dataR = h5read("EXAMPLE_DSET.h5","/ValuesReal");
dataA = h5read("EXAMPLE_DSET.h5","/ValuesApprox");

[X,Y] = meshgrid(0:1/99:1, 0:1/99:1);
surface(X,Y,dataR);
hold on;
surface(X,Y,dataA);
surface(X,Y,dataA - dataR);
hold off;