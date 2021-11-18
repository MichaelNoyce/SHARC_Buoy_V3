% Stewart Platform Routine Code
% Author: Liam Clark
% 21 October, 2018

%% Routine Code
% Perform initial cleanup
cleanup;
% Start Matlab mobile connector if not already running
%if ~connector.isRunning
%    connector on;
%    pause(3);
%end
create_timer;

function create_timer()
stewie = [];
m = [];
plot_enabled = [];
time = [];
log_vals = [];
log_time = [];
log_idx = [];
t=timer;
t.StartFcn = @initTimer;
t.TimerFcn = @timerCallback;
t.Period   = 0.025 ;
t.BusyMode = 'drop';
t.ExecutionMode  = 'fixedRate';
start(t);

    function initTimer(src, event)
        plot_enabled=1;
        try
            stewie = StewartPlatform(152, 18.92, 103, 28.07, 62, 165);
            stewie.connect('COM12');
            stewie.calibrate;
        catch
            % If an error occurs, perform deconstruction
            cleanup;
        end

           % Begin plot
        time = 0;
        if(plot_enabled)
            stewie.plot_platform;
            drawnow;
        end
        % Move the platform into starting position to avoid an initial jolt
        [roll, pitch, yaw, x, y, z] = update(0);
        stewie.set_position(roll, pitch, yaw, x, y, z);
        stewie.move(2.0);
        pause(2);        
    end

    function timerCallback(src, event)
        if time == 0
            tic
        end
        time = toc;
        [roll, pitch, yaw, x, y, z] = update(time);
        stewie.set_position(roll, pitch, yaw, x, y, z);
        %log_time(log_idx,1) = toc;
        %log_vals(log_idx,:) = [yaw, pitch, roll, x, y, z];
        stewie.move(t.Period);
 
    end
    
        if(plot_enabled)
            stewie.update_plot;
            drawnow;
        end
        
        
    end



%% Functions

% Timer interrupt routine - Use this to define your routine!
function [roll, pitch, yaw, x, y, z] = update(time)
roll = 0; %10*sind(360*(time^2)/10);
pitch = 0;
yaw = 0;
x = 0; %5*time;
y = 0;
z = 160 + (10*sind(360*(time)/10));

    if time >= 10
        x = 10;
        roll =  0;
        pitch = 0;
        z = 160;
    end
    
    
    
end

% Delete old timers and unused serial connections
function cleanup()
% Find and delete old timers
for tim = timerfind
    tim.stop;
end
delete(timerfind);
% Delete all usused serial connections
if ~isempty(instrfind)
    fclose(instrfind);
end
delete(instrfind);
% Clear workspace variables
clear;
end

