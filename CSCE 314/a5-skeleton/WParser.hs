module WParser ( parse,
                 wprogram ) where

  import Data.Char
  import Control.Applicative (Applicative(..))
  import Control.Monad       (liftM, ap)
  import W

  -----------------------------
  -- This is the main parser --
  -----------------------------
  wprogram = whitespace >> many stmt >>= \ss -> return $ Block ss
  -- a program is a sequence of statements; the parser returns them
  -- as a single block-statement

  -- only two of the statement types below are supported, 
  -- the rest are undefined.
  -- please implement them

  stmt = varDeclStmt +++ assignStmt +++ ifStmt +++ whileStmt +++ 
         blockStmt +++ emptyStmt +++ printStmt

-- GIVEN
  printStmt = do
    keyword "print"
    e <- expr
    symbol ";"
    return $ Print e

-- GIVEN
  emptyStmt = do 
    symbol ";" 
    return Empty

-- DONE
  varDeclStmt = do
    keyword "var"
    i <- identifier
    symbol "="
    e <- expr
    symbol ";"
    return $ VarDecl i e

-- DONE
  assignStmt = do
    i <- identifier
    symbol "="
    e<- expr
    symbol ";"
    return $ Assign i e

-- DONE
  ifStmt = do
    keyword "if"
    e<- parens expr
    s1<- stmt
    s2 <- (keyword "else" >> stmt) +++ (return Empty)
    return $ If e s1 s2

-- DONE
  whileStmt = do
    keyword "while"
    e<- parens expr
    s<- stmt
    return $ While e s

-- DONE
  blockStmt = do
    symbol "{"
    ms<- many stmt
    symbol "}"
    return $ Block ms

  -- the only kind of expression supported for now is stringLiterals
  -- implement the full expression language of W

-- DONE
  expr = log_expr >>= logicalExprSeq
  logicalExprSeq left =
        (do
                op <- (symbol "&" >> symbol "&" >> return And) +++
                      (symbol "|" >> symbol "|" >> return Or)
                right <- log_expr
                logicalExprSeq (op left right)
        ) +++ return left

-- DONE
  log_expr =(symbol "!" >> log_expr >>= \p -> return (Not p)) +++ comp_expr

-- DONE
  comp_expr = a_expr >>= comparisonExprSeq
  comparisonExprSeq left =
    (do op <- (symbol "=" >> symbol "=" >> return Equals) +++
              (symbol "<" >> symbol "=" >> return LessOrEqual) +++
              (symbol ">" >> symbol "=" >> return GreaterOrEqual) +++
              (symbol "<" >> return Less) +++
              (symbol ">" >> return Greater) +++
              (symbol "!" >> symbol "=" >> return NotEqual)

        right <- a_expr
        comparisonExprSeq (op left right)
    ) +++ return left

-- DONE
  a_expr = term >>= termSeq
  termSeq left =
        ( do op <- (symbol "+" >> return Plus) +++
                   (symbol "-" >> return Minus)
             right <- term
             termSeq (op left right)
        ) +++ return left

-- DONE
  term = factor >>= factorSeq
  factorSeq left =
        ( do op <- (symbol "*" >> return Multiplies)
                    +++ (symbol "/" >> return Divides)
             right <- factor
             factorSeq (op left right)
        ) +++ return left

-- GIVEN
  factor = (nat >>= \n -> return $ Val (VInt n)) +++
           (identifier >>= \n -> return $ Var n)
          +++ stringLiteral +++ parens expr

  -- stringLiterals can contain \n characters
  stringLiteral = do char ('"')
                     s <- many stringChar
                     char ('"')
                     whitespace
                     return $ Val (VString s)

  stringChar = do ( char '\\' >> char 'n' >> return '\n' ) 
               +++ sat (/= '"')

  ----------------------
  -- Parser utilities --
  ----------------------

  keywords = words "var if else while"
  isKeyword s = s `elem` keywords

  keyword s = do 
    s' <- identifier 
    if s' == s then return s else failure     
         
  newtype Parser a = P (String -> [(a, String)])
    
  parse :: Parser a -> String -> [(a, String)]
  parse (P p) inp = p inp
    
  instance Monad Parser where
      -- return :: a -> Parser a
      return v = P $ \inp -> [(v, inp)]
    
      -- (>>=) :: Parser a -> (a -> Parser b) -> Parser b
      p >>= q = P $ \inp -> case parse p inp of 
                              [] -> []
                              [(v, inp')] -> let q' = q v in parse q' inp'
    
  instance Functor Parser where
    fmap = liftM

  instance Applicative Parser where
    pure = return
    (<*>) = ap

  failure :: Parser a
  failure = P $ \_ -> []
    
  item :: Parser Char 
  item = P $ \inp -> case inp of 
                       (x:xs) -> [(x, xs)]
                       [] -> []
    
  -- Parse with p or q
  (+++) :: Parser a -> Parser a -> Parser a
  p +++ q = P $ \inp -> case parse p inp of 
                          [] -> parse q inp
                          [(v, inp')] -> [(v, inp')]
    
    
  -- Simple helper parsers
  sat :: (Char -> Bool) -> Parser Char
  sat pred = do c <- item 
                if pred c then return c else failure
    
  digit, letter, alphanum :: Parser Char
  digit = sat isDigit
  letter = sat isAlpha
  alphanum = sat isAlphaNum
    
  char :: Char -> Parser Char
  char x = sat (== x)
    
  string = sequence . map char 
    
  many1 :: Parser a -> Parser [a]
  many1 p = do v <- p 
               vs <- many p 
               return (v:vs)
    
  many :: Parser a -> Parser [a]
  many p = many1 p +++ return []
    
  -- Useful building blocks
  nat :: Parser Int
  nat = do s <- many1 digit 
           return (read s)
    
  identifier :: Parser String
  identifier = do s <- letter
                  ss <- many alphanum
                  whitespace
                  return (s:ss)

  whitespace :: Parser ()
  whitespace = many (sat isSpace) >> comment
    
  symbol s = do 
    s' <- string s
    whitespace
    return s'    
    
  comment = ( do string "//" 
                 many (sat (/= '\n')) 
                 whitespace ) +++ return ()
  parens p = do 
    symbol "("
    p' <- p
    symbol ")"
    return p'