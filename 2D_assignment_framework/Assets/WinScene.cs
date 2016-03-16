using UnityEngine;
using System.Collections;

public class WinScene : MonoBehaviour {

		public Texture winTexture;

		void OnGUI()
		{
			GUI.DrawTexture(new Rect(0,0,Screen.width,Screen.height), winTexture);
			if (GameStateManager.getLevel () < 2) {
				if (GUI.Button (new Rect (Screen.width / 2, Screen.height / 2 + 50 , 150, 25), "Next Level")) {
					GameStateManager.play ();
				}
				if (GUI.Button (new Rect (Screen.width / 2, Screen.height / 2 + 75, 150, 25), "Quit")) {
					Application.Quit ();
				}
			} else { 
				if (GUI.Button (new Rect (Screen.width / 2, Screen.height / 2 + 50, 150, 25), "Finished all levels!")) {
					Application.Quit ();
				}
			}
		}
	}