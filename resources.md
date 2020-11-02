1. https://cseweb.ucsd.edu/~gill/BWLectSite/Resources/C2U4GT.pdf (Corneil 2003)
2. https://rd.springer.com/content/pdf/10.1007%2F978-3-540-30559-0_1.pdf (Corneil 2004)
3. [Perfect Elimination Orderings and Chordal graph](http://people.math.binghamton.edu/zaslav/Oldcourses/580.S13/bartlett.MC2011_perfectgraphs_wk1_day3.pdf) (have mistype in an describing?)
4. https://www.cse.iitd.ac.in/~naveen/courses/CSL851/uwaterloo.pdf
http://www.cs.kent.edu/~aleitert/iga/slides/06LexBFS
https://rd.springer.com/content/pdf/10.1007%2Fs11590-017-1213-y.pdf
https://arxiv.org/pdf/1704.05115.pdf
https://sms.math.nus.edu.sg/smsmedley/Vol-12-2/On%20transitively%20orientable%20graphs(O%20Chan,%20C%20C%20Chen%20&%20P%20Slater).pdf
https://core.ac.uk/download/pdf/82826493.pdf
http://www.cs.haifa.ac.il/~golumbic/courses/seminar-2013graph/sadjad-unit-interval04.pdf
https://reader.elsevier.com/reader/sd/pii/002001909500046F?token=1B09E2AB63B7097A507206B65D881BC1315EC4900C18D830022F20AA19400398F0ADBB4B8D77AC2BED68673A11B6FE2C
Graph generation:
{
  https://link.springer.com/content/pdf/10.1007/s10479-007-0190-4.pdf
  https://pantheon.ufrj.br/bitstream/11422/1930/1/13_04_000628638.pdf
}


1. **Chordal graph** - a graph with no induced cycle of size greater than three ([link](https://en.wikipedia.org/wiki/Chordal_graph)) or in other words: chordal graph is one in which all cycles of four or more vertices have a chord

  1. **Induced cycle** is a [cycle graph](https://en.wikipedia.org/wiki/Cycle_graph) that is an induced subgraph of G;

  2. **Cycle graph** is a graph, that consists of a **single** (the only) [cycle](https://en.wikipedia.org/wiki/Cycle_(graph_theory))

  3. A graph is chordal if and only if it has a perfect elimination ordering.

2. A **perfect elimination ordering** in a graph is an ordering of the vertices of the graph such that, for each vertex v, v and the neighbors of v that occur after (before) v in the order form a clique. (in a book it was opposite: *...that occur before..*) (tho some books says othewise: [2.4 Defeintion](https://www.cse.iitd.ac.in/~naveen/courses/CSL851/uwaterloo.pdf)says Pred(v) form a clique and 3.2.2 algorithm uses Succ(v))

3. LBFS(G, x) -> usual, label given x <- |A| and so on

4. LBFS+(o) -> arbitary vertex, all vertices are in same cell so 1st step is omitted

5. **Unit interval graph** *(uig)* - an undirected graph G is a unit interval graph if there is an interval representation of G in which all the intervals
have the same length. [Roberts](https://core.ac.uk/download/pdf/82826493.pdf)
  Интервальные графы являются хордальными и, следовательно, совершенными
  Единичные интервальные графы — это интервальные графы, имеющее интервальное представление, в котором каждый интервал имеет единичную длину.
  1. UIG = Indifference graph = special case of chordal


5. #### Graph autogeneration

1. [Here](https://link.springer.com/content/pdf/10.1007/s10479-007-0190-4.pdf) at **procedure** insert_query we have "*G + (u,v) is chordal, if..*" but actually it's "*G + (u,v) preserves chordality*" which means, that it not ruins it, but it not fulfilll it (? - no, iy\s all correct because we start from a tree and it will njot connect vertices which are violating chordailty);

2. First step: link a three

3. Use insert_query m times. Instead of randomly grabbing u,v vertices (lately we'll encounter v,u order and that's a minor problem) I can grab edges from E' - a complement graph's edges (but initializing it will cost O(n^2), so it's not a big deal, plus it will cost memory, so pure is better BUT it will be cool to check it and compare);

(20k will cost ~17sec to generate whereas clique-based methor 0.0005s)
