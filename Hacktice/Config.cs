using System.Runtime.InteropServices;

namespace Hacktice
{
    [StructLayout(LayoutKind.Sequential)]
    public class Config
    {
        // TODO: I am assuming zero initialization here. Is it fair?
        public byte lAction;
        public byte showButtons;
        public byte stickStyle;
        public byte speed;

        public byte wallkickFrame;
        public byte dpadDownAction;
        public byte cButtonsAction;
        public byte lRAction;

        public byte distanceFromClosestPanel;
        public byte distanceFromClosestPiranha;
        public byte distanceFromClosestSecret;
        public byte distanceFromClosestRed;

        public byte stateSaveStyle;
        public byte timerStopOnCoinStar;
        public byte timerStyle;
        public byte timerShow;

        public byte warpWheel;
        public byte dpadUpAction;
        public byte deathAction;
        public byte muteMusic;

        public byte checkpointLava;
        public byte checkpointPole;
        public byte checkpointDoor;
        public byte checkpointWallkick;

        public byte checkpointWarp;
        public byte checkpointCannon;
        public byte checkpointBurning;
        public byte checkpointGroundpound;

        public byte checkpointPlatform;
        public byte checkpointObject;
        public byte checkpointCoin;
        public byte checkpointRed;

        // since version 1.3.6
        public byte name3 = (byte)'C';
        public byte name2 = (byte)'A';
        public byte name1 = (byte)'R';
        public byte name0 = (byte)'P';

        public byte name7 = (byte)'E';
        public byte name6 = (byte)'C';
        public byte name5 = (byte)'I';
        public byte name4 = (byte)'T';

        public byte showName;
        public byte _nameReserved;
        public byte name9;
        public byte name8;

        public void setName(string name)
        {
            _nameReserved = 0;
            name0 = name1 = name2 = name3 = name4 = name5 = name6 = name7 = name8 = name9 = 0;
        }

        // TODO: Do this better please
        public bool Equals(Config o)
        {
            return lAction == o.lAction
                && showButtons == o.showButtons
                && stickStyle == o.stickStyle
                && speed == o.speed
                && wallkickFrame == o.wallkickFrame
                && dpadDownAction == o.dpadDownAction
                && cButtonsAction == o.cButtonsAction
                && lRAction == o.lRAction
                && distanceFromClosestPanel == o.distanceFromClosestPanel
                && distanceFromClosestSecret == o.distanceFromClosestSecret
                && distanceFromClosestPiranha == o.distanceFromClosestPiranha
                && distanceFromClosestRed == o.distanceFromClosestRed
                && stateSaveStyle == o.stateSaveStyle
                && timerStopOnCoinStar == o.timerStopOnCoinStar
                && timerShow == o.timerShow
                && timerStyle == o.timerStyle
                && deathAction == o.deathAction
                && muteMusic == o.muteMusic
                && checkpointLava == o.checkpointLava
                && checkpointPole == o.checkpointPole
                && checkpointDoor == o.checkpointDoor
                && checkpointWallkick == o.checkpointWallkick
                && checkpointWarp == o.checkpointWarp
                && checkpointCannon == o.checkpointCannon
                && checkpointBurning == o.checkpointBurning
                && checkpointGroundpound == o.checkpointGroundpound
                && checkpointPlatform == o.checkpointPlatform
                && checkpointObject == o.checkpointObject
                && checkpointCoin == o.checkpointCoin
                && checkpointRed == o.checkpointRed
                && dpadUpAction == o.dpadUpAction
                && warpWheel == o.warpWheel
                && showName == o.showName;
        }
    }
}
