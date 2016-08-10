
-- Assignment 2, CSCE-314
-- Section: 501
-- Student Name: Dalton Harris
-- UIN: 123002242
-- (Acknowledge any help received here)

module Main where

import Test.HUnit
import System.Exit

--1 DONE
factorial :: Int -> Int
factorial 0 = 1
factorial n = n * factorial(n-1)

--2 DONE
fibonacci :: Int -> Int
fibonacci 0 = 0
fibonacci 1 = 1
fibonacci n = fibonacci(n-1) + fibonacci(n-2)

--3 DONE
mySum :: [Int] -> Int
mySum [] = 0
mySum (x:xs) = x + mySum(xs)

--4 DONE
flatten :: [[a]] -> [a]
flatten [] = []
flatten (x:xs) = x ++ flatten(xs)

--5 DONE
myLength :: [a] -> Int
myLength [] = 0
myLength (_:xs) = 1 + myLength(xs)

--6 DONE
isElement :: Eq a => a -> [a] -> Bool
isElement x [] = False
isElement x (y:ys) = if x == y then True else isElement x ys

type Set a = [a]

--7
mkSet :: Eq a => [a] -> Set a
mkSet [] = []
mkSet (x:xs) = if isElement x xs then mkSet xs else x : mkSet xs

--8
size ::  Set a -> Int
size [] = 0
size [x] = 1
size (_:xs) = 1 + myLength(xs)

--9
subset :: Eq a => Set a -> Set a -> Bool 
subset [][] = True
subset [] ys = True
subset (x:xs) [] = False 
subset (x:xs)(ys) = if (isElement x ys) then (subset xs ys) else False

--10
setEqual :: Eq a => Set a -> Set a -> Bool
setEqual [][] = True
setEqual []ys = False
setEqual xs[] = False
setEqual xs ys = if subset xs ys && (myLength xs == myLength ys) then True else False

--11
powerset :: Set a -> Set (Set a)
powerset [] = [[]]
powerset (x:xs) = powerset xs ++ [x:y | y <- powerset xs]

myTestList = 
  TestList [ 
    "factorial" ~: factorial 3 ~=? 6
    
    , "fibonacci" ~: fibonacci 4 ~=? 3

    , "mySum" ~: mySum [1..10] ~=? 55
    
    , "flatten 1" ~: flatten [[]::[Int]] ~=? []
    , "flatten 2" ~: flatten [[]::[Int], [], []] ~=? []
    , "flatten 3" ~: flatten [[1], [2, 3, 4], [], [5, 6]] ~=? [1, 2, 3, 4, 5, 6]
      
    , "myLength" ~: myLength [1, 2, 3] ~=? 3
      
    , "isElement 1" ~: (isElement 'c' "abcd") ~=? True
    , "isElement 2" ~: (isElement 'e' "abcd") ~=? False
      
    , "mkSet 1" ~: size (mkSet "abcdaab") ~=? 4
    , "mkSet 2" ~: size (mkSet "abc") ~=? 3
      
    , "subset 1" ~: subset (mkSet "dbdb") (mkSet "abcdaab") ~=? True
    , "subset 2" ~: subset (mkSet "abc") (mkSet "bcccbhk") ~=? False
      
    , "setEqual 1" ~: setEqual (mkSet "abc") (mkSet "abcf") ~=? False
    , "setEqual 2" ~: setEqual (mkSet "abccbac") (mkSet "cbabc") ~=? True
      
    , "powerset 1" ~: size (powerset (mkSet []::[Int])) ~=? 1
    , "powerset 2" ~: size (powerset (mkSet [1])) ~=? 2
    , "powerset 3" ~: size (powerset (mkSet [1, 2])) ~=? 4
    ]

main = do c <- runTestTT myTestList
          putStrLn $ show c
          let errs = errors c
              fails = failures c
          exitWith (codeGet errs fails)
          
codeGet errs fails
 | fails > 0       = ExitFailure 2
 | errs > 0        = ExitFailure 1
 | otherwise       = ExitSuccess
