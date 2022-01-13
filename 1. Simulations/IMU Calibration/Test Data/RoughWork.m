
%length = length(out.tout);
%length2 = length(out.simout.Data(:,1);
timeSeries = out.tout;
acceleration = double(out.simout.Data);
accelerationTimeSeries = [timeSeries acceleration(1:26600,:)];


gyro = double(out.simout1.Data);
gyroTimeSeries = [timeSeries gyro];

