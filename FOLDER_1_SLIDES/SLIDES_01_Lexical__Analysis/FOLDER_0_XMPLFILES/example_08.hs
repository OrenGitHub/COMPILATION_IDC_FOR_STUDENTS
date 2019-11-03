main = do
  putStrLn("-2-2=?")
  x <- readLn
  if (x < -4) then putStrLn("Y")
              else putStrLn("N")
