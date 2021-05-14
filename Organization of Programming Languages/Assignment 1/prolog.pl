% Peyton Somerville
% Source: http://rosettacode.org/wiki/Matrix_multiplication#Prolog

% To run: type 'swipl' and use this code in the interpreter
% To test: type 'mmult([[1,2],[3,4]],[[5,6],[7,8]],X).' this is for multiplying two 2x2 matrices


% SWI-Prolog has transpose/2 in its clpfd library
:- use_module(library(clpfd)).						% importing library			
 
% N is the dot product of lists V1 and V2.
dot(V1, V2, N) :- maplist(product,V1,V2,P), sumlist(P,N).		% creates a list P based on V1 and V2 and adds up list to N
product(N1,N2,N3) :- N3 is N1*N2.					% multiplies N1 and N2 and puts in N3
 
% Matrix multiplication with matrices represented
% as lists of lists. M3 is the product of M1 and M2
mmult(M1, M2, M3) :- transpose(M2,MT), maplist(mm_helper(MT), M1, M3).	% multiply matrix M1 and M2 and put in M3
mm_helper(M2, I1, M3) :- maplist(dot(I1), M2, M3).			% binds to M3