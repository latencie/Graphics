using UnityEngine;
using System.Collections;

public class GameOverScene : MonoBehaviour {

	public Texture gameOverTexture;

	void OnGUI()
	{
		GUI.DrawTexture(new Rect(0,0,Screen.width,Screen.height), gameOverTexture);
		if (GameStateManager.getLives () > 0) {
			if (GUI.Button (new Rect (Screen.width / 2, Screen.height / 2 + 50 , 150, 25), "Try again")) {
				GameStateManager.play ();
			}
			if (GUI.Button (new Rect (Screen.width / 2, Screen.height / 2 + 75, 150, 25), "Give up")) {
				Application.Quit ();
			}
		} else { 
			if (GUI.Button (new Rect (Screen.width / 2, Screen.height / 2 + 50, 150, 25), "Better luck next time")) {
				Application.Quit ();
			}
		}
	}
}