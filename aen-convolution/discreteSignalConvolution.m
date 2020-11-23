clc
clear all
close all

disp('- KONVOLUSYON HESABI -');
disp('(!) Baslangic noktalarini tam sayi olarak giriniz.');
disp('(!) Sinyalleri [. . .] seklinde giriniz.');
x_str = input('x[t] için t baslangic noktasi: ');
x = input('x[t] = '); % x[t]
h_str = input('h[t] için t baslangic noktasi: ');
h = input('h[t] = '); % h[t]

m = length(x); % x[t] değer sayısı
n = length(h); % h[t] değer sayısı
l = m+n-1; % y[t] değer sayısı
y_str = x_str + h_str; % y[t] başlangıç

% benim konvolüsyon kodum
y1 = zeros(1,l); % benim y[t] sinyalim
for i = 1:m % x[t]'nin değeri
    for j = 1:n % h[t]'nin iterasyonu
        %{
        her iterasyonda bir y[t] değerinin bir kısmı
        örneğin y[1]:
        x[2] h[1] iken y[1]'in bir kısmı ...
        x[1] h[2] iken y[1]'in diğer bir kısmı ...
        ve hepsinin üst üste eklenmesi.
        %}
        y1(i+j-1) = y1(i+j-1) + h(j)*x(i);
    end
end

% hazır konvolüsyon fonksiyonu
y2 = conv(x,h); % fonksiyonun y[t] sinyali

% sonuçları yazdırma
arr_all = [x h y1 y2];
max = max(abs(arr_all)); % grafik y değeri için maximum

subplot(221) % x[t] sinyali
stem(x_str:x_str+m-1, x, 'filled'),
set(gca,'xlim',[x_str x_str+l-1]), % x düzlemi aralığı
set(gca,'ylim',[-max max]), % y düzlemi aralığı
ylabel('x[t]'), xlabel('t'), grid on,
title('1. Sinyal');

subplot(222) % h[t] sinyali
stem(h_str:h_str+n-1, h, 'filled'),
set(gca,'xlim',[h_str h_str+l-1]),
set(gca,'ylim',[-max max]),
ylabel('h[t]'), xlabel('t'), grid on,
title('2. Sinyal');

subplot(223) % benim hesapladığım y[t] sinyali
stem(y_str:y_str+l-1, y1, 'filled'),
set(gca,'xlim',[y_str y_str+l-1]),
set(gca,'ylim',[-max max]),
ylabel('y[t]'), xlabel('t'), grid on,
title('Benim Konvolusyonum');

subplot(224) % fonksiyonun y[t] sinyali
stem(y_str:y_str+l-1, y2, 'filled'),
set(gca,'xlim',[y_str y_str+l-1]),
set(gca,'ylim',[-max max]),
ylabel('y[t]'), xlabel('t'), grid on,
title('Fonksiyonun Konvolusyonu');