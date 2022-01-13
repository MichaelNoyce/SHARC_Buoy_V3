fs = 100;                         % sampling frequency
N = 512;                           % signal length
sig = zeros(1,N);                   % create sig buffer
n = 0:(N-1);                       

%Create 1kHz tone
fk = 1;                          % signal frequency
A = 0.8;                            % peak amplitude
sig = A * sin(2*pi*n*fk/fs);        % create sampled sine signal

%Quantize sig to f32 fixed point
sig_fixed = fi(sig,1,32,18);             % fi(source, signed, word length,  fraction length (best precision)

%plot sig_fixed
plot(sig_fixed);

%Split sig_fixed from one string to array of strings
sig_fixed = tostring(sig_fixed);
sig_fixed_split = regexp(sig_fixed,'\s*','split');

%Print sig_fixed to a file
file = fopen('fixed-sine.c','w');
cols = 8;
for i = 0:cols:N-1
    for j = 1:cols
        fprintf(file,'%s, ',char(sig_fixed_split(i+j)));
    end
    fprintf(file,'\n');
end

fclose(file);                             %You must manually delete the comma after the last entry in the file!!