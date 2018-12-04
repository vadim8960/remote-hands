%% Setup manipulator:

robot = robotics.RigidBodyTree;

% Denavit–Hartenberg manipulator parameters:
dhparams = [0    pi/2  5    0;
            9.5	 0     0    0;
            7	 0     0    0;
            6.5  0     0    0;
            0    pi/2  0    0;
            4    0     0    0];

% Setup manipulator nodes:
node1 = robotics.RigidBody('node1');
node2 = robotics.RigidBody('node2');
node3 = robotics.RigidBody('node3');
node4 = robotics.RigidBody('node4');
node5 = robotics.RigidBody('node5');
node6 = robotics.RigidBody('node6');

% Setup manipulator joints:
joint1 = robotics.Joint('joint1', 'revolute');
joint2 = robotics.Joint('joint2', 'revolute');
joint3 = robotics.Joint('joint3', 'revolute');
joint4 = robotics.Joint('joint4', 'revolute');
joint5 = robotics.Joint('joint5', 'revolute');
joint6 = robotics.Joint('joint6', 'revolute');

% Transform joints with DH parameters:
setFixedTransform(joint1, dhparams(1,:), 'dh');
setFixedTransform(joint2, dhparams(2,:), 'dh');
setFixedTransform(joint3, dhparams(3,:), 'dh');
setFixedTransform(joint4, dhparams(4,:), 'dh');
setFixedTransform(joint5, dhparams(5,:), 'dh');
setFixedTransform(joint6, dhparams(6,:), 'dh');

% Assign joints to manipulator nodes:
node1.Joint = joint1;
node2.Joint = joint2;
node3.Joint = joint3;
node4.Joint = joint4;
node5.Joint = joint5;
node6.Joint = joint6;

% Assemble manipulator:
addBody(robot, node1, robot.BaseName);
addBody(robot, node2, 'node1');
addBody(robot, node3, 'node2');
addBody(robot, node4, 'node3');
addBody(robot, node5, 'node4');
addBody(robot, node6, 'node5');

%% TCP connection to bracers:

% Create TCP connection:
t = tcpip('localhost', 7247);
set(t, 'InputBufferSize', 1000);
fopen(t);

% Receive data from TCP connection:
while true
    while (get(t, 'BytesAvailable') > 0) 
        received = fscanf(t);
        disp(received);
    end 
end

%% Rotate acceleration:

% acc = [0.3 0.1 0.9];
% q = [0.1 0.2 0.3 0.4];
% rotacc = quatrotate(q, acc);
% disp(acc);
% disp(rotacc);

%% Solve inverse kinematics:

% % Create inverse kinematics solver:
% ik = robotics.InverseKinematics('RigidBodyTree', robot);
% ik.RigidBodyTree = robot;
% 
% % Setup parameters for solving inverse kinematics:
% homeConf = homeConfiguration(robot);
% target = getTransform(robot, homeConf, 'node6', 'base');
% targetPoint = [8 10 18];
% target(1:3, 4) = targetPoint;
% weights = [0.01 0.01 0.01 1 1 1];
% 
% % Solve inverse kinematics:
% [ikSolution, ikInfo] = ik('node6', target, weights, homeConf);

%% Serial connection to manipulator:

% s = serial('/dev/ttyUSB0');
% fopen(s);
% fprintf(s, solutionPositions(ikSolution));

%% Other + cleanup:

% Show manipulator model and info:
showdetails(robot);
show(robot, ikSolution);
hold all;
scatter3(targetPoint(1), targetPoint(2), targetPoint(3), 'r*', 'linewidth', 20);
hold off;

% Clean up TCP connection:
% fclose(t); 
% delete(t); 
% clear t 

%% Function definitions:

function f = solutionPositions(solution)
    % Get vector of positions for inverse kinematics solution.
    s = size(solution);
    result = zeros(s);
    for i = 1:s
        result(1, i) = solution(1, i).JointPosition;
    end
    f = result;
end