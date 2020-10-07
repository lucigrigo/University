% Colocviu 2 Teoria Sistemelor

disp('--------------------- sistemul dat -------------------')
A = [1 1; -7 -2]
B = [1 0 ; 0 2]
C = [1 7]
D = zeros(1, 2)
system = ss(A, B, C, D);

disp('--------------------- matricea de transfer -------------------')
H = tf(system)

disp('--------------------- stabilitate -------------------')
eig(A) % polii lui A
isstable(system) % este sistemul stabil sau nu?

disp('--------------------- controlabilitate -------------------')
R = ctrb(system) % matricea de controlabilitate
rank(R)

disp('--------------------- observabilitate -------------------')
Q = obsv(system) % matricea de observabilitate
rank(Q)

disp('--------------------- minimalitate -------------------')
system_minimal = ss(system, 'min') % este acelasi cu sistemul initial