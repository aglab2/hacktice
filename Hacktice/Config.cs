using System.Runtime.InteropServices;

namespace Hacktice
{
    [StructLayout(LayoutKind.Sequential)]
    public class Config
    {
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

        public byte _reserved1;
        public byte _reserved0;
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
                && _reserved1 == o._reserved1
                && _reserved0 == o._reserved0
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
                && checkpointRed == o.checkpointRed;
        }
    }
}
