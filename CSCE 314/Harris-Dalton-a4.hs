-- Assignment 4, CSCE-314
-- Section: 501
-- Student Name: Dalton Harris
-- UIN: 123002242

module Main where

import Prelude hiding (lookup)

import Test.HUnit
import System.Exit

-- AST definition for W
data WValue = VInt Int 
            | VBool Bool 
              deriving (Eq, Show)

data WExp = Val WValue
          | Var String

          | Plus WExp WExp
          | Minus WExp WExp
          | Multiplies WExp WExp
          | Divides WExp WExp

          | Equals WExp WExp
          | NotEqual WExp WExp
          | Less WExp WExp
          | Greater WExp WExp
          | LessOrEqual WExp WExp
          | GreaterOrEqual WExp WExp

          | And WExp WExp
          | Or WExp WExp
          | Not WExp

data WStmt = Empty
           | VarDecl String WExp
           | Assign String WExp
           | If WExp WStmt WStmt
           | While WExp WStmt
           | Block [WStmt]

type Memory = [(String, WValue)]


-- Integer Functions
myplusfunction :: WValue -> WValue -> WValue
myplusfunction (VInt var1) (VInt var2) = VInt (var1 + var2)
myplusfunction _ _ = error "Addition Input Error"

myminusfunction :: WValue -> WValue -> WValue
myminusfunction (VInt var1) (VInt var2) = VInt (var1 - var2)
myminusfunction _ _ = error "Subtraction Input Error"

mymultiply :: WValue -> WValue -> WValue
mymultiply (VInt var1) (VInt var2) = VInt (var1 * var2)
mymultiply _ _ = error "Multiplication Input Error"

mydivide :: WValue -> WValue -> WValue
mydivide (VInt var1) (VInt var2) = VInt (quot var1 var2)
mydivide _ _ = error "Division Input Error"


-- Boolean Functions
myequals :: WValue -> WValue -> WValue
myequals (VInt val1) (VInt val2) = VBool (val1 == val2)
myequals _ _ = error "Equality Input Error"

mynotequals :: WValue -> WValue -> WValue
mynotequals (VInt val1) (VInt val2) = VBool (val1 /= val2)
mynotequals _ _ = error "Inequality Input Error"

mylessthan :: WValue -> WValue -> WValue
mylessthan (VInt val1) (VInt val2) = VBool (val1 < val2)
mylessthan _ _ = error "Less Than Input Error"

mygreaterthan :: WValue -> WValue -> WValue
mygreaterthan (VInt val1) (VInt val2) = VBool (val1 > val2)
mygreaterthan _ _ = error "Greater Than Input Error"

mylessthanorequal :: WValue -> WValue -> WValue
mylessthanorequal (VInt val1) (VInt val2) = VBool (val1 <= val2)
mylessthanorequal _ _ = error "Less Than or Equal Input Error"

mygreaterthanorequal :: WValue -> WValue -> WValue
mygreaterthanorequal (VInt val1) (VInt val2) = VBool (val1 >= val2)
mygreaterthanorequal _ _ = error "Greater Than or Equal Input Error"


-- Logical Expression Functions
myand :: WValue -> WValue -> WValue
myand (VBool val1) (VBool val2) = VBool (val1 && val2)
myand _ _ = error "AND Input Error"

myor :: WValue -> WValue -> WValue
myor (VBool val1) (VBool val2) = VBool (val1 || val2)
myor _ _ = error "OR Input Error"

mynot :: WValue -> WValue
mynot (VBool val1) = VBool (not val1)
mynot _ = error "NOT Input Error"

marker = ("|", undefined)
isMarker (x, _) = x == "|"

-- eval function
eval :: WExp -> Memory -> WValue
eval (Val x) val1 = x
eval (Var s) xs = case lookup s xs of
          Nothing -> error (s ++ "Error: Not Found")
          Just v -> v
eval (Plus w1 w2) val1 = myplusfunction (eval w1 val1) (eval w2 val1)
eval (Minus w1 w2) val1 =  myminusfunction (eval w1 val1) (eval w2 val1)
eval (Multiplies w1 w2) val1 = mymultiply (eval w1 val1) (eval w2 val1)
eval (Divides w1 w2) val1 = mydivide (eval w1 val1) (eval w2 val1)
--eval (Equals w1 w2) val1 = myequals (eval w1 val1) (eval w2 val1)

eval (Equals (Val v1) (Val v2)) m = VBool (v1 == v2)
eval (Equals e1 e2) m = eval (Equals (Val (eval e1 m)) (Val (eval e2 m))) m

eval (NotEqual w1 w2) val1 = mynotequals (eval w1 val1) (eval w2 val1)
eval (Less w1 w2) val1 = mylessthan (eval w1 val1) (eval w2 val1)
eval (Greater w1 w2) val1 = mygreaterthan (eval w1 val1) (eval w2 val1)
eval (LessOrEqual w1 w2) val1 = mylessthanorequal (eval w1 val1) (eval w2 val1)
eval (GreaterOrEqual w1 w2) val1 = mygreaterthanorequal (eval w1 val1) (eval w2 val1)
eval (And w1 w2) val1 = myand (eval w1 val1) (eval w2 val1)
eval (Or w1 w2) val1 = myor (eval w1 val1) (eval w2 val1)
eval (Not w1) val1 = mynot (eval w1 val1)

-- exec function
exec :: WStmt -> Memory -> Memory
exec Empty m = m
exec (VarDecl str w) a 
                    | (lookup str a) == Nothing = (str, (eval w a)) : a
                    | otherwise = error ("'" ++ str ++ "' already declared")

exec (Assign s e) m = rFDF s (eval e m) m where 
	rFDF _ _ [] = error $ "undefined variable" ++ s
	rFDF s v (x@(k,_):xs)
		| s == k = if samekind v x then (k,v):xs else error "type error in statement"
		| otherwise = x:rFDF s v xs where
			samekind v@(VInt _) x@(_, VInt _) = True
			samekind v@(VBool _) x@(_, VBool _) = True
			samekind _ _ = False

exec (Block ss) m = popMarker $ foldr exec (marker : m) (reverse ss)
              where popMarker [] = []
                    popMarker (x:xs) | isMarker x = xs
                                     | otherwise = popMarker xs

exec (If w1 s1 s2) a
                  | eval w1 a == VBool( True ) = exec s1 a
                  | eval w1 a == VBool( False ) = exec s2 a
                  
exec (While w1 s1) a = if ( eval w1 a == VBool( True ) ) then exec (While w1 s1) (exec s1 a) else a                      


prog2 = Assign "x"  (Val (VInt 0))
prog2_m = [("x",VInt 3)]

prog3 = While ((Greater (Var "x") (Val (VInt 0))))
     (Assign "x" (Minus (Var "x") (Val (VInt 1))))
prog3_m = [("x", VInt 5)]

-- example programs
testprogram1 = Block
     [
       VarDecl "x" (Val (VInt 0)),
       VarDecl "b" (Greater (Var "x") (Val (VInt 0))),
       If (Or (Var "b") (Not (GreaterOrEqual (Var "x") (Val (VInt 0)))))
         ( Block [ Assign "x" (Val (VInt 1)) ] )
         ( Block [ Assign "x" (Val (VInt 2)) ] )
     ]

factorial = 
  Block
  [
    VarDecl "acc" (Val (VInt 1)),
    While (Greater (Var "arg") (Val (VInt 1)))
    (
      Block
      [
        Assign "acc" (Multiplies (Var "acc") (Var "arg")),
        Assign "arg" (Minus (Var "arg") (Val (VInt 1)))         
      ]
    ),
    Assign "result" (Var "acc")
  ]


fibonacci = Block
        [
            VarDecl "i" (Val (VInt 1)),
            VarDecl "fib" (Val (VInt 1)),
            VarDecl "t1" (Val (VInt 0)),
            VarDecl "t2" (Val (VInt 1)),
            While ( Less (Var "i") (Var "x"))
            (
                Block   [
                    Assign "fib" (Plus (Var "t1") (Var "t2")),
                    Assign "t1" (Var "t2"),
                    Assign "t2" (Var "fib"),
                    Assign "i" (Plus (Var "i") (Val (VInt 1)))
                        ]
            )
        ]


myprogram1 = Plus (Val(VInt 100)) (Val(VInt 100))
myprogram2 = Minus (Val(VInt 256)) (Val(VInt 200))
myprogram3 = Multiplies (Val(VInt 100)) (Val(VInt 100))
myprogram4 = Divides (Val(VInt 1000)) (Val(VInt 100))

myprogram5 = Block
      [
        If (Equals (Var "a") (Var "b"))
          (Assign "a" (Val (VBool True)))
          (Assign "b" (Val (VBool False)))
      ]

myprogram5_m = [("a",(VInt 1)), ("b",(VInt 1))]
  
myprogram6 = Block
      [
        If (NotEqual (Var "c") (Var "d"))
          (Assign "c" (Val (VBool True)))
          (Assign "c" (Val (VBool False)))
      ]

myprogram6_m = [("c",(VInt 1)), ("d",(VInt 2))]

myprogram7 = Block
      [
        While ( Greater (Var "f") (Var "e"))
        (
          Block [ Assign "e" (Plus (Var "e") (Val (VInt 1)) ) ]
        )
      ]

myprogram7_m = [("e",(VInt 0)), ("f",(VInt 3))]

myprogram8 = Block
      [
        While ( GreaterOrEqual (Var "h") (Var "g"))
        (
          Block [ Assign "g" (Multiplies (Var "g") (Val (VInt 50)) ) ]
        )
      ]

myprogram8_m = [("g",(VInt 1)), ("h",(VInt 100))]

myprogram9 = Block
      [
        While ( Less (Var "i") (Var "j"))
        (
          Block [ Assign "i" (Multiplies (Var "i") (Val (VInt 12)) ) ]
        )
      ]

myprogram9_m = [("i",(VInt 3)), ("j",(VInt 9))]

myprogram10 = Block
      [
        While ( LessOrEqual (Var "l") (Var "k"))
        (
          Block [ Assign "l" (Plus (Var "l") (Val (VInt 25)) ) ]
        )
      ]

myprogram10_m = [("k",(VInt 16)), ("l",(VInt 2))]

myprogram11 = Block
      [
        If (And (Var "m") (Var "n"))
          ( Block[ Assign "n" (Val (VBool True)) ] )
          ( Block[ Assign "n" (Val (VBool False)) ] )
      ]

myprogram11_m = [("m",(VBool False)), ("n",(VBool True))]

myprogram12 = Block
      [
        If (Or (Var "o") (Var "p"))
          ( Block[ Assign "p" (Val (VBool True)) ] )
          ( Block[ Assign "p" (Val (VBool False)) ] )
      ]

myprogram12_m = [("o",(VBool True)), ("p",(VBool False))]

myprogram13 = Block
      [
        If ( Not (Var "q"))
          ( Block[ Assign "q" (Val (VBool True)) ] )
          ( Block[ Assign "q" (Val (VBool False)) ] )
      ]

myprogram13_m = [("q",(VBool False))]

myprogram14 = Block
      [
        If (NotEqual (Var "pow") (Val (VInt 0)))
          (
            Block
            [
              While ( Less (Var "pow") (Val (VInt 4)))
              (
                Block[ Assign "pow" (Multiplies (Var "pow") (Val (VInt 2))) ]
              )
            ]
          )
          ( Block[ Assign "pow" (Val (VInt 0)) ] )
      ]

myprogram14_m = [("pow",(VInt 2))]

myprogram15 = Block
      [
        VarDecl "abc" (Val (VInt 0)),
        VarDecl "abc" (Val (VInt 1))
      ]

myprogram16 = Block
      [
        Assign "xyz" (Val (VInt 0))
      ]
  
  
-- some useful helper functions
lookup s [] = Nothing
lookup s ((k,v):xs) | s == k = Just v
                    | otherwise = lookup s xs

asInt (VInt v) = v
asInt x = error $ "Expected number but got " ++ show x

asBool (VBool v) = v
asBool x = error $ "Expected boolean but got " ++ show x

fromJust (Just v) = v
fromJust Nothing = error "Expected value in Maybe but got Nothing"

-- unit tests
myTestList = TestList [test $ assertEqual "testprogram1" [] (exec testprogram1 []),

    let res = lookup "result" (exec factorial [("result", VInt (-1)), ("arg", VInt 5)])
    in test $ assertBool "factorial of 5" (120 == asInt (fromJust res))

    , "2. Addition" ~: asInt(eval myprogram1 []) ~=? 200
    , "3. Subtraction" ~: asInt(eval myprogram2 []) ~=? 56
    , "4. Multiplication" ~: asInt(eval myprogram3 []) ~=? 10000
    , "5. Division" ~: asInt(eval myprogram4 []) ~=? 10
    
    -- These errors below need to be fixed.
    , "6. Equal" ~: asBool (fromJust (lookup "result" (exec myprogram5 myprogram5_m))) ~=? False
    , "7. Not Equal" ~: asBool (fromJust (lookup "c" (exec myprogram6 myprogram6_m))) ~=? True

    , "8. Greater Than" ~: asInt (fromJust (lookup "e" (exec myprogram7 myprogram7_m))) ~=? 3
    , "9. Greater Than or Equal To" ~: asInt (fromJust (lookup "g" (exec myprogram8 myprogram8_m))) ~=? 2500
    , "10. Less Than" ~: asInt (fromJust (lookup "i" (exec myprogram9 myprogram9_m))) ~=? 36
    , "11. Less Than or Equal To" ~: asInt (fromJust (lookup "l" (exec myprogram10 myprogram10_m))) ~=? 27
    , "12. And" ~: asBool (fromJust (lookup "n" (exec myprogram11 myprogram11_m))) ~=? False
    , "13. Or" ~: asBool (fromJust (lookup "p" (exec myprogram12 myprogram12_m))) ~=? True
    , "14. Not" ~: asBool (fromJust (lookup "q" (exec myprogram13 myprogram13_m))) ~=? True
    , "15. Power 2" ~: asInt (fromJust (lookup "pow" (exec myprogram14 myprogram14_m))) ~=? 4
    
    -- Errors below are intentional, disregard the messages.
    , "16. INTENTIONAL ERROR: Equal" ~: asInt (fromJust (lookup "a" (exec myprogram5 []))) ~=? 0
    , "17. INTENTIONAL ERROR: Less Than" ~: asBool (fromJust (lookup "i" (exec myprogram9 []))) ~=? True
    , "18. INTENTIONAL ERROR: Not Equal" ~: asBool (fromJust (lookup "z" (exec myprogram6 []))) ~=? True
    , "19. INTENTIONAL ERROR: Assignment" ~: asInt (fromJust (lookup "xyz" (exec myprogram16 []))) ~=? 0
    , "20. Fibonacci" ~: asInt (fromJust (lookup "fib" (exec fibonacci [("x", VInt 4)]))) ~=? 3
    ]    

main = do c <- runTestTT myTestList
          putStrLn $ show c
          let errs = errors c
              fails = failures c
          if (errs + fails /= 0) then exitFailure else return ()