subtractIntegers :: Integer -> Integer -> Integer
subtractIntegers x y = x - y

main :: IO ()
main =  do

putStr "Reduce x by y using - sign = "
print(subtractIntegers 1700 25)