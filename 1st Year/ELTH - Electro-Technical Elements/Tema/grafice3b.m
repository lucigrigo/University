% graphics_toolkit('gnuplot');
rez = 0.2:0.1:20;
tem = 13;
r_int = 0;      % din echivalarea circuitului
int = tem ./ (rez + r_int);
tens = rez .* int;

figure(1);
grid on;
plot(tens);
plot(rez);
title('Caracteristica de functionare a generatorului echivalent si a rezistentei');

figure(2);
% tens_prag = 0.6;
% tens_termica = 0.025;
% tens_dioda = -10:0.2:10;
% coef_emisie = 2;
% int_sat = 10 ^ (-1);
% ec_dioda = int_sat * (exp(tens_dioda / (0.26)) - 1);
% % plot(tem);
% plot(tens_dioda);
% % graf = digits(ec_dioda);
% % plot(graf);
% grid on;
% title('Graficul rezultat dupa inlocuirea rezistentei cu o dioda semiconductoare');


% rezolvarea punctului static pentru dioda foloind metoda iterativa
%  Intrari:
%          Is = curent saturatie dioda
%          k = mkT/q
% 	       E = tensiunea electromotoare a sursei
%          R = rezistenta serie
%          N = numarul de iteratii
%          er = eroarea minima
%Ud = zeros(N,1);
%Id = zeros(N,1);
Is = 0.00001;
kc = 0.026;
Ein = 13;
R = 4;
N = 100;
er = 0.00000001;
Ud(1,1) = 0;      % prima valoare pentru Ud
Id(1,1) = Ein/R;  % curent de scurtcircuit 
i = 2;
ter = 1;
while((er < abs(ter)) && (i < N)) % repeta daca eroarea este mai mare decat cea impusa sau numarul                                     %de iteratii este mai mic decat N
    Ud(i,1) = kc*log(Id(i-1,1)/Is+1);
    Id(i,1) = (Ein-Ud(i,1))/R; 
    ter = Ud(i,1)-Ud(i-1,1) % parametru de control al erorii 
    i = i + 1;
endwhile
% ajustare afisare grafica
% construiesc dreptele pentru metoda iterativa
Udp(1,1) = Ud(1,1);
Idp(1,1) = Id(1,1);
for i = 1:1:length(Ud)-1
    Udp(2*i,1) = Ud(i+1,1);
    Udp(2*i+1,1) = Ud(i+1,1);
    Idp(2*i,1) = Id(i,1);
    Idp(2*i+1,1) = Id(i+1,1);
endfor
Efin = 1.2*Ud(length(Ud), 1); % tensiunea pe dioda 1.2 * Udps
Estep = Efin/N;
pUd = [0:Estep:Efin];
pId = Is*(exp(pUd/kc)-1);
pIr = (Ein - pUd)/R;
% plot(pUd, pId, '-or', pUd, pIr, '-xb', Udp, Idp, '-g');
plot(pUd, pId, '-or', pUd, pIr);
title('Punctul static dioda redresoare polarizare directa'); 
