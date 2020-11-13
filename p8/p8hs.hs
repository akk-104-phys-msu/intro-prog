import System.IO (hFlush,stdout)
-- $$\int \frac{\sin x}{\sqrt{x}} =
--  \sum_{i=0}^{\infty} (-1)^{i}\frac{x^{2i+3/2}}{(2i+1)!(2i+3/2)}$$
fromInt :: Int -> Double
fromInt = fromIntegral
analyticAntideriv ε x = sum pos + sum neg
  where
    newTerm t x i = -t * x^2 * (i + 3/2) / ((i+2)*(i+3)*(i+7/2))
    firstTerm = 2/3*x**(3/2)
    terms lst@((t,i):_) =
      if abs t < ε then lst
      else terms $! (newTerm t x i, i+2):lst
    vals = fst <$> terms [(firstTerm, 0)]
    pos = filter (>= 0) vals
    neg = filter (< 0) vals  
analyticIntegral ε _ a b = (0, analyticAntideriv ε b - analyticAntideriv ε a)
--numDiff f ε x = (f(x+ε) - f (x-ε)) / (2*ε)

pieceSize a b n = (b - a) / fromInt n

rectangleFixed f n a b =
  dx * sum [f (a + dx*(i'+λ)) | i<-[0..n-1], let i' = fromInt i]
  where dx = pieceSize a b n
        λ = 0.9

trapezoidFixed f n a b =
  1/2 * dx * sum [f an + f bn | i <- [0..n-1],
                  let i' = fromInt i
                      an = a + i'*dx
                      bn = an + dx]
  where dx = pieceSize a b n

simpsonFixed f n a b = dx/3 * (f a + s + f b)
  where dx = pieceSize a b n
        s = sum [4*f an + 2*f(an+dx) | i <- [1,3..n-1], let an = a+dx*fromInt i]

simpleQuadratureBuilder q ε f a b =
  let err (_, x, y) = abs (x - y) >= ε 
      (i, _, r) = head $ dropWhile err
        [(n, q f (2^n) a b, q f (2^(n+1)) a b) | n <- [0..]]
  in (i, r)

rectangleSimple = simpleQuadratureBuilder rectangleFixed
trapezoidSimple = simpleQuadratureBuilder trapezoidFixed
simpsonSimple = simpleQuadratureBuilder simpsonFixed

rectangle ε f a b =
  let iter s dx n i =
        let i' = i+1; dx'=dx/2; n'=2*n
            s' = s + sum [f (a+fromInt i*dx') | i<-[1,3..n'-1]]
            v = s * dx; v' = s' * dx'
        in if abs (v-v') >= ε
           then (iter $! s') dx' n' i'
           else (i, v')
  in iter 0 (b-a) 1 0

trapezoid ε f a b =
  let ya = f a; yb = f b
      ev s dx = dx*(ya+yb+2*s)/2
      iter s dx n i =
        let i' = i+1; dx'=dx/2; n'=2*n
            s' = s + sum [f (a+fromInt i*dx') | i<-[1,3..n'-1]]
        in if abs (ev s dx - ev s' dx') < ε
           then (i, ev s' dx')
           else (iter $! s') dx' n' i'
  in iter 0 (b-a) 1 0

simpson ε f a b =
  let ya = f a
      yb = f b
      ev s1 s2 dx = dx/3 * (ya + 4*s1 + 2*s2 + yb)
      iter s1 s2 dx n i =
        let n' = n * 2
            dx' = dx/2
            i' = i + 1
            s1' = sum [f (a+fromInt i*dx') | i <- [1,3..n'-1]]
            s2' = s1 + s2
            v = ev s1 s2 dx
            v' = ev s1' s2' dx'
        in if abs (v - v') < ε
           then (i, v')
           else (iter $! s1') s2' dx' n' i'
  in iter 0 0 (b-a) 1 0

f x = sin x / sqrt x
a = pi / 2
b = pi

main = do
  putStr "Введите ε: "
  hFlush stdout
  ε <- readLn
  let res = map (\g -> g ε f a b) $ reverse [rectangle,trapezoid,simpson,analyticIntegral]
      titles = reverse ["прямоугольников", "трапеций"
                       , "Симпсона", "полуаналитический"]
      format m (i, v) = "Метод "++m++" рассчитал значение "
                        ++show v++" за "++show i++" итерации.\n"
  mapM_ (\s -> putStr s >> hFlush stdout) $ zipWith format titles res
