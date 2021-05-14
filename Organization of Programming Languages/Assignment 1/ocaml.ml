(* Peyton Somerville *)
(* Source: http://rosettacode.org/wiki/Matrix_multiplication#OCaml *)

(* To run: type 'ocaml' then paste the program into the interpreter and hit enter *)
(* Then type: 'matrix_multiply [|[|1;2|];[|3;4|]|] [|[|5;6|];[|7;8|]|] ;;' this is for multiplying two 2x2 matrices *)
(* ctrl-Z to exit ocaml interpreter *)

let matrix_multiply x y =				(* function declaration taking two inputs *)
  let x0 = Array.length x				(* declaring array to represent matrix 1 *)
  and y0 = Array.length y in				(* declaring array to represent matrix 2*)
  let y1 = if y0 = 0 then 0 else Array.length y.(0) in	(* if a matrix is 0 then make new one *)
  let z = Array.make_matrix x0 y1 0 in			(* declaring array for result matrix based on matrix 1 and 2*)
  for i = 0 to x0-1 do
    for j = 0 to y1-1 do				(* triple for-loop to access each element of all 3 matrices *)
      for k = 0 to y0-1 do		
        z.(i).(j) <- z.(i).(j) + x.(i).(k) * y.(k).(j)	(* matrix multiplication formula *)
      done
    done						(* done ends the for-loops *)
  done;
  z							(* displays the result matrix *)
  ;;							(* ;; means end of program *)