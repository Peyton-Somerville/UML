-- Peyton Somerville
-- Source: http://rosettacode.org/wiki/Matrix_multiplication#Ada

-- To compile: type 'gnatmake Ada.ada'
-- To run: type './Ada'

with Ada.Text_IO;               use Ada.Text_IO;	-- importing libraries
with Ada.Numerics.Real_Arrays;  use Ada.Numerics.Real_Arrays;
 
procedure Matrix_Product is				-- function declaration				
 
   procedure Put (X : Real_Matrix) is
      type Fixed is delta 0.01 range -100.0..100.0;	-- limits to numbers -100 to 100
   begin
      for I in X'Range (1) loop
         for J in X'Range (2) loop			-- double for loop to access each element in matrix
            Put (Fixed'Image (Fixed (X (I, J))));
         end loop;
         New_Line;
      end loop;						-- end loop to finish for-loops
   end Put;
 
   A : constant Real_Matrix :=				-- matrix 1
         (  ( 1.0,  1.0,  1.0,   1.0),
            ( 2.0,  4.0,  8.0,  16.0),
            ( 3.0,  9.0, 27.0,  81.0),
            ( 4.0, 16.0, 64.0, 256.0)
         );
   B : constant Real_Matrix :=				-- matrix 2
         (  (  4.0,     -3.0,      4.0/3.0,  -1.0/4.0 ),
            (-13.0/3.0, 19.0/4.0, -7.0/3.0,  11.0/24.0),
            (  3.0/2.0, -2.0,      7.0/6.0,  -1.0/4.0 ),
            ( -1.0/6.0,  1.0/4.0, -1.0/6.0,   1.0/24.0)
         );
begin
   Put (A * B);						-- matrix multiplication, Ada has built in capabilities to do it
end Matrix_Product;