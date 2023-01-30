%Student id's
student1 = single([2 0 2 2 9 1 0 6 0])
student2 = single([2 0 2 2 6 7 3 4 8])
%Signal vectors to be populated
x1 = []
x2 = []
%Next populate the signal vectors
for i = 1:100
    x1 = cat(2,x1,student1)
    x2 = cat(2,x2,student2)
end

%Cast to floats as assignment specifies floats
x1 = single(x1)
x2 = single(x2)

%Calculate avg of signals
meanX1 = mean(x1)
meanX2 = mean(x2)

%Subtract mean to produce zero-mean signals
x1 = x1 - meanX1
x2 = x2 - meanX2

fs = round((1060+7348)/2)

figure 
plot(x1(1:27))
title('Student1 Signal')
xlabel('Sample Number') 
ylabel('Amplitude')

figure 
plot(x2(1:27))
title('Student2 Signal')
xlabel('Sample Number') 
ylabel('Amplitude')

fftPoints = 1024
normalisedFreqs = [1:(fftPoints/2)]/(fftPoints/2)
x1Fft = fft(x1,fftPoints)
x2Fft = fft(x2,fftPoints)
%Remove -'ve frequencies
x1Fft = x1Fft(1:512)
x2Fft = x2Fft(1:512)

% credit to https://www.gaussianwaves.com/2014/07/how-to-plot-fft-using-matlab-fft-of-basic-signals-sine-and-cosine-waves/
figure
plot(normalisedFreqs,abs(x1Fft))
title('Student1 1024 Point Normalised FFT')
xlabel('Normalised Frequency')
ylabel('Magnitude')
%axis([0 0.5 0 1000])

figure
plot(normalisedFreqs,abs(x2Fft))
title('Student2 1024 Point Normalised FFT')
xlabel('Normalised Frequency')
ylabel('Magnitude')
%axis([0 0.5 0 1000])

[val1,ind1] = max(abs(x1Fft))
[val2,ind2] = max(abs(x2Fft))

strongestComponentFrequencyX1 = normalisedFreqs(ind1)
strongestComponentFrequencyX2 = normalisedFreqs(ind2)

%After exporting weights to Matlab workspace as Num
%keptWeights1 = Num(39:70)


%*************************************************
%===========NOW DO FIR FILTERING=============%
%*****************************************************

%thanks tohttps://uk.mathworks.com/help/matlab/data_analysis/filtering-data.html
filteredx1 = filter(weights1single,1,x1)
x1filteredFft = fft(filteredx1,fftPoints)
x1filteredFft = x1filteredFft(1:512)
figure
plot(normalisedFreqs,abs(x1filteredFft))
title('Student1 1024 Point Normalised FFT of Filtered Data')
xlabel('Normalised Frequency')
ylabel('Magnitude')
%axis([0 0.5 0 1000])

filteredx2 = filter(weights2single,1,x2)
x2filteredFft = fft(filteredx2,fftPoints)
x2filteredFft = x2filteredFft(1:512)
figure
plot(normalisedFreqs,abs(x2filteredFft))
title('Student2 1024 Point Normalised FFT of Filtered Data')
xlabel('Normalised Frequency')
ylabel('Magnitude')
%axis([0 0.5 0 1000])

