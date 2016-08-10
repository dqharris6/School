-- Assignment 3, CSCE-314
-- Section: 501
-- Student Name: Dalton Harris
-- UIN: 123002242
-- (Acknowledge any help received here)

module Main where

import Test.HUnit
import System.Exit
import Data.List
import Data.Char

-- DONE
triads :: Int -> [(Int, Int, Int)]
triads n = [ (x,y,z) | x <- [2 .. n] , y <- [x+1 .. n] , z <- [y+1 .. n] , x*x + y*y == z*z ]

-- generates list of factors to be used with function perfect below
factor :: Int -> [Int]
factor 0 = []
factor n = [x | x<-[1..n], mod n x == 0, not (x == n)]

-- DONE
perfect :: [Int]
perfect = [x | x<-[1..], sum (factor x) == x]

-- merges two sorted lists
merge :: Ord a => [a] -> [a] -> [a]
merge [] [] = []
merge xs [] = xs
merge [] ys = ys
merge (x:xs) (y:ys) = if x <= y
 then x : merge xs (y:ys)
 else y : merge (x:xs) ys

-- mergeP is a parameterized merge
mergeP :: Ord a => (a -> a -> Bool) -> [a] -> [a] -> [a]
mergeP pred [] [] = []
mergeP pred xs [] = xs
mergeP pred [] ys = ys
mergeP pred (x:xs) (y:ys) = 
 case pred x y of
 True -> x : mergeP pred xs (y:ys)
 False -> y : mergeP pred (x:xs) ys
 
-- DONE
mergeSort :: Ord a => [a] -> [a]
mergeSort [] = []
mergeSort [x] = [x]
mergeSort xs = merge (mergeSort a) (mergeSort b)
 where (a, b) = splitAt (length xs `div` 2) xs

-- DONE
mergeSortBy :: Ord a => (a -> a -> Bool) -> [a] -> [a]
mergeSortBy pred [] = []
mergeSortBy pred [x] = [x]
mergeSortBy pred xs
    = mergeP pred (mergeSortBy pred a) (mergeSortBy pred b)
    where
    (a, b) = splitAt (length xs `div` 2) xs

-- DONE
multiply :: [Int] -> Int
multiply = foldr (*) 1

-- DONE
concatenate :: [String] -> String     
concatenate = foldl (++) ""

-- DONE
concatenateAndUpcaseOddLengthStrings :: [String] -> String
concatenateAndUpcaseOddLengthStrings [] = ""
concatenateAndUpcaseOddLengthStrings xs = map toUpper (concatenate ([y | y<-xs, odd (length y)]))

-- DONE
insertionSort :: Ord a => [a] -> [a]
insertionSort = foldr insert []

-- DONE
maxElementOfAList :: Ord a => [a] -> a 
maxElementOfAList xs = foldr1 max xs

-- DONE
keepInBetween :: Int -> Int -> [Int] -> [Int]
keepInBetween a b xs = [x | x <- xs, x >= a, x <= b]

-- DONE
data Tree a b = Branch b (Tree a b) (Tree a b)
              | Leaf a
instance (Show a, Show b) => Show (Tree a b) where
 show (Leaf a) = "leaf: " ++ (show a)
 show (Branch b l r) = "branch: " ++ (show b) ++ "{" ++ (show l) ++ "," ++ (show r) ++ "}"    

preorder  :: (a -> c) -> (b -> c) -> Tree a b -> [c]
postorder :: (a -> c) -> (b -> c) -> Tree a b -> [c]
inorder   :: (a -> c) -> (b -> c) -> Tree a b -> [c]

-- DONE
preorder map1 map2 (Leaf n) = [x] where
 x = map1 n
preorder map1 map2 (Branch b l r) = [x] ++ y ++ z where
 x = map2 b
 y = preorder map1 map2 l
 z = preorder map1 map2 r
 
-- DONE 
postorder map1 map2 (Leaf n) = [x] where
 x = map1 n
postorder map1 map2 (Branch b l r) = x ++ y ++ [z] where
 x = postorder map1 map2 l
 y = postorder map1 map2 r
 z = map2 b

-- DONE
inorder map1 map2 (Leaf n) = [x] where
 x = map1 n
inorder map1 map2 (Branch b l r) = x ++ [y] ++ z where
 x = inorder map1 map2 l
 y = map2 b
 z = inorder map1 map2 r
 

data E = IntLit Int
       | BoolLit Bool
       | Plus E E
       | Minus E E
       | Multiplies E E
       | Divides E E
       | Equals E E
         deriving (Eq, Show)

eval :: E -> E
eval (BoolLit boo) = BoolLit boo
eval (IntLit a) = IntLit a
eval (Plus (IntLit a) (IntLit b)) = IntLit $ a + b 
eval (Minus (IntLit a) (IntLit b)) = IntLit $ a - b
eval (Multiplies (IntLit a) (IntLit b)) = IntLit $ a * b
eval (Divides (IntLit a) (IntLit  b)) = IntLit $ quot a b
eval (Equals (BoolLit a) (BoolLit b)) = BoolLit $ (a == b)

mytree = Branch "A" 
           (Branch "B" 
              (Leaf 1) 
              (Leaf 2)) 
           (Leaf 3)

program = Equals 
            (Plus (IntLit 1) (IntLit 2))
            (Minus
             (IntLit 5)
             (Minus (IntLit 3) (IntLit 1)))
    
myTestList =

  let te s e a = test $ assertEqual s e a
      tb s b = test $ assertBool s b

  in
    TestList [ 
        tb "triads 1" $ [(3, 4, 5)] == triads 5
      , tb "triads 2" $ [(3, 4, 5), (6, 8, 10)] == ( sort $ triads 10)

      , tb "perfect" $ take 3 perfect == [6, 28, 496]
        
      , te "mergeSort 1" " adhllowy" (mergeSort "howdy all") 
      , te "mergeSort 2" "" (mergeSort "") 
      , te "mergeSort 3" "x" (mergeSort "x") 
        
      , te "mergeSortBy 1" " 'eggim" (mergeSortBy (<) "gig 'em") 
      , te "mergeSortBy 2" "nmlkieecbbaJ  " (mergeSortBy (>) "Jack be nimble")
      , te "mergeSortBy 3" "" (mergeSortBy (<) "")

      , te "multiply" 10 (multiply [-2, -1, 5])
      , te "concatenate" "ABCD" (concatenate ["AB", "", "", "C", "D", ""])

      , te "concatenateAndUpcaseOddLengthStrings"
          "HERE'S AN EXAMPLE" (concatenateAndUpcaseOddLengthStrings ["here's ", "an ", "a ", "example"])

      , te "insertionSort" "  Jabcceikkqu" (insertionSort "Jack be quick")
      , te "max in a list" 100 (maxElementOfAList [3, 100, 0])
      , te "keepInBetween" [3,0,20,2] (keepInBetween 0 20 [77, 3, -1, 0, 21, 20, -9, 2])

      , te "preorder" "AB123" (concatenate (preorder show id mytree))
      , te "postrder" "12B3A" (concatenate (postorder show id mytree))
      , te "inorder" "1B2A3" (concatenate (inorder show id mytree))

      , te "eval" (BoolLit True) (eval program)
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