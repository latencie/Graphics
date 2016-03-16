using UnityEngine;
using System.Collections;

public class WelcomeScene : MonoBehaviour {

	public Texture black;

	void OnGUI()
	{
		GUI.DrawTexture(new Rect(0,0,Screen.width,Screen.height), black);
		if (GUI.Button (new Rect (Screen.width / 2, Screen.height / 2 + 50, 150, 25), "Play")) {
			GameStateManager.play ();
			}
	}
}
