using System;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

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
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 28)]
        public byte[] customText;

        public byte _pad1;
        public byte _pad0;
        public byte softReset;
        public byte showCustomText;

        public void SetCustomText(string _name)
        {
            var name = _name.ToUpper().Trim();
            customText = new byte[28];
            for (int i = 0; i < customText.Length; i++)
            {
                int ibase = i / 4;
                int ioff = i % 4;
                int namePos = ibase * 4 + (3 - ioff);
                if (namePos < name.Length)
                {
                    customText[i] = (byte) name[namePos];
                }
                else
                {
                    customText[i] = 0;
                }
            }
            customText[24] = 0;
        }

        public string GetCustomText()
        {
            StringBuilder builder = new StringBuilder();
            try
            {
                for (int i = 0; i < customText.Length; i++)
                {
                    int ibase = i / 4;
                    int ioff = i % 4;
                    int namePos = ibase * 4 + (3 - ioff);
                    byte b = customText[namePos];
                    if (b != 0)
                    {
                        builder.Append((char)b);
                    }
                    else
                    {
                        break;
                    }
                }
            }
            catch (Exception)
            { }
            return builder.ToString();
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
                && Enumerable.SequenceEqual(customText, o.customText)
                && softReset == o.softReset
                && showCustomText == o.showCustomText;
        }
    }
}
