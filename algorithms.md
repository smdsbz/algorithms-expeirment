## Closest Pair

$$
\begin{align}
&\text{CLOSEST-PAIR}(X, Y) \\
&\hspace{1em} \textbf{if} \ X.length \leq 3 \ \textbf{do} \\
&\hspace{2em} // \ \text{暴力求解该集合内最近点对} \\
&\hspace{2em} \delta := \min_{p_i, p_j \in X} \{ \Vert p_i - p_j \Vert \} \\
&\hspace{2em} \text{return} \ \delta \\
&\hspace{1em} \textbf{else} \\
&\hspace{2em} // \ \text{将点集分为左半和右半} \\
&\hspace{2em} k := \lceil X.length / 2 \rceil \\
&\hspace{2em} x_s := \frac{1}{2} \cdot (X[k - 1].x + X[k].x) \\
&\hspace{2em} X_l, X_r := X[1:k - 1], X[k:X.length] \\
&\hspace{2em} \text{let} \ Y_l, Y_r \ \text{be new lists.} \\
&\hspace{2em} \textbf{for} \ p \in Y, \ \textbf{do} \\
&\hspace{3em} \textbf{if} \ p \in X_l, \ \textbf{do} \\
&\hspace{4em} Y_l.append(p) \\
&\hspace{3em} \textbf{else} \\
&\hspace{4em} Y_r.append(p) \\
&\hspace{3em} \textbf{end if} \\
&\hspace{2em} \textbf{end for} \\
&\hspace{2em} // \ \text{递归调用以求出左半和右半中最近点对} \\
&\hspace{2em} \delta_l := \text{CLOSEST-PAIR}(X_l, Y_l) \\
&\hspace{2em} \delta_r := \text{CLOSEST-PAIR}(X_l, Y_l) \\
&\hspace{2em} \delta_m := \min \{ \delta_l, \delta_r \} \\
&\hspace{2em} // \ \text{讨论横跨两点集的情况} \\
&\hspace{2em} \text{let} \ Y_m' \ \text{be new list.} \\
&\hspace{2em} \textbf{for} \ p = (x, y) \in Y, \ \textbf{do} \\
&\hspace{3em} \textbf{if} \ x \in [x_s - \delta_m, x_s + \delta_m], \ \textbf{do} \\
&\hspace{4em} Y_m'.append(p) \\
&\hspace{3em} \textbf{end if} \\
&\hspace{2em} \textbf{end for} \\
&\hspace{2em} \textbf{for} \ i = 1 \, \dots \, Y_m'.length - 1, \ \textbf{do} \\
&\hspace{3em} \textbf{for} \ j = i + 1 \, \dots \, \min\{ i + 8, Y_m'.length \}, \ \text{do} \\
&\hspace{4em} \delta_m = \min \{ \delta_m, \Vert Y_m'[i], Y_m'[j] \Vert \} \\
&\hspace{3em} \textbf{end for} \\
&\hspace{2em} \textbf{end for} \\
&\hspace{2em} \text{return} \ \delta_m \\
&\hspace{1em} \textbf{end if} \\
\end{align}
$$

Initially, call $$\text{CLOSEST-PAIR}(\mathrm{sort}(P, \lambda(p): p.x), \mathrm{sort}(P, \lambda(p): p.y))$$ on full question set $$P$$.  

## Big Number Multiplication

$$
\begin{align}
&\text{BIG-NUMBER-MULTIPLICATION}(A, B) \\
&\hspace{1em} \textbf{if} \ A.length = 2 \, , \ \textbf{do} \\
&\hspace{2em} \text{return} \ A \times B \\
&\hspace{1em} \textbf{end if} \\
&\hspace{1em} A' := \vert A \vert \\
&\hspace{1em} B' := \vert B \vert \\
&\hspace{1em} \text{left-pad} \ ``0\text{''} \ \text{to} \ A', B', \ \text{such that} \ A'.length = B'.length = 2^{k} \, ( k \in \mathbb{Z} ) \, . \\
&\hspace{1em} \text{let} \ A_h', A_l', B_h', B_l' \ \text{be new numbers, s.t.} \ A' = \overline{A_h' \, A_l'}, B' = \overline{B_h' \, B_l'}, \\
&\hspace{3em} \text{and} \ A_h'.length = A_l'.length = B_h'.length = B_l'.length \, . \\
&\hspace{1em} R_h := A_h' \times B_h' \\ 
&\hspace{1em} R_l := A_l' \times B_l' \\
&\hspace{1em} R_m := (A_h'+ A_l') \times (B_h' + B_l') - (r_h + r_l) \\
&\hspace{1em} R := \overline{R_h \, R_m \, R_l} \\
&\hspace{1em} \textbf{if} \ A < 0 \, \oplus \, B < 0 \, , \ \textbf{do} \\
&\hspace{2em} \text{return} \ {-R} \\
&\hspace{1em} \textbf{end if} \\
&\hspace{1em} \text{return} \ R \\
\end{align}
$$

## Output Optimal BST

$$
\begin{align}
&\text{CONSTRUCT-OPTIMAL-BST}(root, f, t, s, mode) \\
&\hspace{1em} \textbf{if} \ f > t \, , \ \textbf{do} \\
&\hspace{2em} \textbf{if} \ mode = ``\text{left''} \, , \ \textbf{do} \\
&\hspace{3em} \text{print} \ ``\text{d''} , t , ``\text{ is k''} , t + 1 , ``\text{'s left child''} \\
&\hspace{2em} \textbf{else} \\
&\hspace{3em} \text{print} \ ``\text{d''} , f - 1 , ``\text{ is k''} , f - 1 , ``\text{'s right child''} \\
&\hspace{2em} \textbf{end if} \\
&\hspace{2em} \text{return} \\
&\hspace{1em} \textbf{end if} \\
&\hspace{1em} i := root[f][t] \\
&\hspace{1em} \textbf{if} \ mode = ``\text{left''} \, , \ \textbf{do} \\
&\hspace{2em} \text{print} \ ``\text{k''} , i , ``\text{ is k''} , s , ``\text{'s left child''} \\
&\hspace{1em} \textbf{else if} \ mode = ``\text{right''} \, , \textbf{do} \\
&\hspace{2em} \text{print} \ ``\text{k''} , i , ``\text{ is k''} , s , ``\text{'s right child''} \\
&\hspace{1em} \textbf{else} \\
&\hspace{2em} \text{print} \ ``\text{k''} , i , ``\text{ is root''} \\
&\hspace{1em} \textbf{end if} \\
&\hspace{1em} \text{CONSTRUCT-OPTIMAL-BST}(root, f, i - 1, i, ``\text{left''}) \\
&\hspace{1em} \text{CONSTRUCT-OPTIMAL-BST}(root, i + 1, t, i, ``\text{right''}) \\
&\hspace{1em} \text{return} \\
\end{align}
$$

Initially, call $$\text{CONSTRUCT-OPTIMAL-BST}(root, 1, root.columns, \text{NIL}, ``\text{root''})$$.  

## Floyd-Warshall

$$
\begin{align}
&\text{FLOYD-WARSHALL}(W) \\
&\hspace{1em} n := W.rows \\
&\hspace{1em} \text{let} \ \Pi[1 \, \dots \, n][1 \, \dots \, n] \ \text{be new matrix.} \\
&\hspace{1em} \textbf{for} \ i = 1 \, \dots \, n \, , \textbf{do} \\
&\hspace{2em} \textbf{for} \ j = 1 \, \dots \, n \, , \textbf{do} \\
&\hspace{3em} \textbf{if} \ i = j \ \text{or} \ W[i][j] = {+\infty} \, , \textbf{do} \\
&\hspace{4em} \Pi[i][j] = \mathrm{NIL} \\
&\hspace{3em} \textbf{else} \\
&\hspace{4em} \Pi[i][j] = i \\
&\hspace{3em} \textbf{end if} \\
&\hspace{2em} \textbf{end for} \\
&\hspace{1em} \textbf{end for} \\
&\hspace{1em} D := W \\
&\hspace{1em} \textbf{for} \ k = 1 \, \dots \, n \, , \textbf{do} \\
&\hspace{2em} \textbf{for} \ i = 1 \, \dots \, n \, , \textbf{do} \\
&\hspace{3em} \textbf{for} \ j = 1 \, \dots \, n \, , \textbf{do} \\
&\hspace{4em} t := D[i][k] + D[k][j] \\
&\hspace{4em} \textbf{if} \ t < D[i][j] \, , \textbf{do} \\
&\hspace{5em} D[i][j] = t \\
&\hspace{5em} \Pi[i][j] = \Pi[k][j] \\
&\hspace{4em} \textbf{end if} \\
&\hspace{3em} \textbf{end for} \\
&\hspace{2em} \textbf{end for} \\
&\hspace{1em} \textbf{end for} \\
&\hspace{1em} \text{return} \ D, \Pi
\end{align}
$$























