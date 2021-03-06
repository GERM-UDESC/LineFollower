#include "SERIAL_COMMUNICATION.h"

Communication *Communication::ptCommunication;

Communication::Communication(Controller *LineFollower_, USART *Serial_)
{
	LineFollower = LineFollower_;
	Serial = Serial_;
	Communication::ptCommunication = this;
	counter = 0;
	command = robotStop;
};

void Communication::HandlerByTime()
{
	Communication::ptCommunication->Handler();	
};

void Communication::Handler()
{
	if ((command != robotStop) && (command != robotRun))
	{
		if (counter < bitsToSend)
		{
			doCommand();
			counter++;
		}
		else
		{
			command = robotStop;
			counter = 0;
		};
	}
	else
	{
		verifyCommand();
		doCommand();
	};
};

void Communication::doCommand()
{
	switch (command)
	{
		case robotStop:
			LineFollower->stop();
		break;
		
		case robotRun:
			LineFollower->start(v_ref_ini, 0);
		break;
		
		case sendV_W:
			temporary[0] = LineFollower->Robot.getV();
			temporary[1] = LineFollower->Robot.getW();
			Serial->sendFloat(&temporary[0]);
			Serial->sendFloat(&temporary[1]);
		break;
		
		case sendV_Wcontrol:
			temporary[0] = LineFollower->getVcontrol();
			temporary[1] = LineFollower->getWcontrol();
			Serial->sendFloat(&temporary[0]);
			Serial->sendFloat(&temporary[1]);
		break;
		
		case sendV_W_and_V_Wcontrol:
			temporary[0] = LineFollower->Robot.getV();
			temporary[1] = LineFollower->Robot.getW();
			temporary[2] = LineFollower->getVcontrol();
			temporary[3] = LineFollower->getWcontrol();
			Serial->sendFloat(&temporary[0]);
			Serial->sendFloat(&temporary[1]);
			Serial->sendFloat(&temporary[2]);
			Serial->sendFloat(&temporary[3]);
		break;
		
		case sendLineReading:
			temporary[0] = LineFollower->Robot.getLinePosition();
			temporary[1] = LineFollower->Robot.getLineAngle();
			Serial->sendFloat(&temporary[0]);
			Serial->sendFloat(&temporary[1]);
		break;
		
		case sendMotorsSpeed:
			temporary[0] = LineFollower->Robot.motorD.Get_Speed();
			temporary[1] = LineFollower->Robot.motorE.Get_Speed();
			Serial->sendFloat(&temporary[0]);
			Serial->sendFloat(&temporary[1]);
		break;
		
		case sendMotorsSpeedAndControl:
			temporary[0] = LineFollower->Robot.motorD.Get_Speed();
			temporary[1] = LineFollower->Robot.motorE.Get_Speed();
			temporary[2] = LineFollower->Robot.motorD.getU();
			temporary[3] = LineFollower->Robot.motorE.getU();
			Serial->sendFloat(&temporary[0]);
			Serial->sendFloat(&temporary[1]);
			Serial->sendFloat(&temporary[2]);
			Serial->sendFloat(&temporary[3]);
		break;
		
		case sendMotorsSpeedControlAndErrors:
			temporary[0] = LineFollower->Robot.motorD.Get_Speed();
			temporary[1] = LineFollower->Robot.motorE.Get_Speed();
			temporary[2] = LineFollower->Robot.motorD.getU();
			temporary[3] = LineFollower->Robot.motorE.getU();
			temporary[4] = LineFollower->Robot.motorD.getE();
			temporary[5] = LineFollower->Robot.motorE.getE();
			Serial->sendFloat(&temporary[0]);
			Serial->sendFloat(&temporary[1]);
			Serial->sendFloat(&temporary[2]);
			Serial->sendFloat(&temporary[3]);
			Serial->sendFloat(&temporary[4]);
			Serial->sendFloat(&temporary[5]);
		break;
		
		case sendEverything:
			temporary[0] = LineFollower->Robot.getV();
			temporary[1] = LineFollower->Robot.getW();
			temporary[2] = LineFollower->getVcontrol();
			temporary[3] = LineFollower->getWcontrol();
			temporary[4] = LineFollower->Robot.getLinePosition();
			temporary[5] = LineFollower->Robot.getLineAngle();
			temporary[6] = LineFollower->Robot.motorD.Get_Speed();
			temporary[7] = LineFollower->Robot.motorE.Get_Speed();
			temporary[8] = LineFollower->Robot.motorD.getU();
			temporary[9] = LineFollower->Robot.motorE.getU();
			temporary[10] = LineFollower->Robot.motorD.getE();
			temporary[11] = LineFollower->Robot.motorE.getE();
			Serial->sendFloat(&temporary[0]);
			Serial->sendFloat(&temporary[1]);
			Serial->sendFloat(&temporary[2]);
			Serial->sendFloat(&temporary[3]);
			Serial->sendFloat(&temporary[4]);
			Serial->sendFloat(&temporary[5]);
			Serial->sendFloat(&temporary[6]);
			Serial->sendFloat(&temporary[7]);
			Serial->sendFloat(&temporary[8]);
			Serial->sendFloat(&temporary[9]);
			Serial->sendFloat(&temporary[10]);
			Serial->sendFloat(&temporary[11]);
		break;
		
		case sendPositionAndOrientation:
			temporary[0] = LineFollower->Robot.getX();
			temporary[1] = LineFollower->Robot.getY();
			temporary[2] = LineFollower->Robot.getTeta();
			temporary[3] = LineFollower->getXline();
			temporary[4] = LineFollower->getYline();
			Serial->sendFloat(&temporary[0]);
			Serial->sendFloat(&temporary[1]);
			Serial->sendFloat(&temporary[2]);
			Serial->sendFloat(&temporary[3]);
			Serial->sendFloat(&temporary[4]);
		break;
		
		case sendPWMandEncoderDataRight:
			temporary[0] = LineFollower->Robot.motorD.pwmMotor.getWritedPWM();
			temporary[1] = LineFollower->Robot.motorD.encoder.getSpeed();
			Serial->sendFloat(&temporary[0]);
			Serial->sendFloat(&temporary[1]);
		break;
		
		case sendMotorDdata:
			temporary[0] = LineFollower->Robot.motorD.Get_Speed();
			temporary[1] = LineFollower->Robot.motorD.getU();
			temporary[2] = LineFollower->Robot.motorD.getE();
			temporary[3] = LineFollower->Robot.motorD.Speed_Reference;
			Serial->sendFloat(&temporary[0]);
			Serial->sendFloat(&temporary[1]);
			Serial->sendFloat(&temporary[2]);
			Serial->sendFloat(&temporary[3]);
		break;
		
		default:
			LineFollower->stop();
		
	};
};

void Communication::waitForCommand()
{
	command = Serial->Receive();
	if (command != robotStop)
	{
		LineFollower->start(v_ref_ini, 0);
	}
};

void Communication::verifyCommand()
{
	if (Serial->Available())
	{
		command = Serial->Receive();
		if (command != robotStop)
		{
			LineFollower->start(v_ref_ini, 0);
		}
	}
};




