# ChekersAlphaBeta

A dámajáték szabályai:  

A játékosok felváltva lépnek, a bábuk előre, az ellenfél felé léphetnek mégpedig mindig átlósan csak egy mezőt haladhatnak egyszerre.
A dámajátékban úgy lehet ütni, hogy átugorjuk az ellenfél figuráját, ezáltal növelve a saját pontszámunk.
 Az ütés részletes szabályai:
  1. Csak előre lehet ütni, és csak akkor, ha az átugrandó figura mögötti
  mező üres. 
  2. Ebből következőleg a tábla szélén álló figurát nem lehet
     leütni. 
  3. Nem lehet leütni saját figuránkat, és leütés nélkül átugrani
sem. 
  4. A klasszikus dámajáték szabályai szerint az ütés kötelező. Ez azt
jelenti, hogy ha a soron következő játékosnak ütési lehetősége van,
mindenképpen ütnie kell; természetesen ő választ a lehetséges ütések közül,
ha több figurájának is módja van ütni, illetve ugyanaz a figura több irányba
üthet.
A játék akkor ér véget, amikor az egyik játékosnak elfogytak a bábui, vagy egyetlen bábuja sem tud lépni.

Implementálás:

Minimax és alfa-béta nyesésre alapozik
Kezdetben meg kell adni a koordinátáit annak a bábunak mellyel lépni szeretnénk, amennyiben a lépés helyes megadjuk annak a poziciónak a koordinátáit, ahová lépni szeretnénk.
