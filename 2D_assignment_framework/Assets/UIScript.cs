using UnityEngine;
using System.Collections;

/*
 * Maintains the UI throughout the levels
 */
public class UIScript : MonoBehaviour {

	public int score;
	public int lives;
	public int displayTime;
	public float nextTime;
	public int timeInterval;	
	public float startTime;

	// Use this for initialization
	void Start () {
		score = 0;
		GameStateManager.setTime ();
		timeInterval = 1;
		startTime = GameStateManager.getTime ();
		displayTime = (int) (Time.time - startTime);
		nextTime = Time.time + timeInterval;

	}

	void OnGUI(){
		if (Time.time >= nextTime) {
			displayTime = (int)(Time.time - GameStateManager.getTime ());
				nextTime += timeInterval;
			}
			updateScreen ();
	}

	void updateScreen(){
		GUI.Box(new Rect(10, 10, 200, 30), "score: " + GameStateManager.getScore());
		GUI.Box(new Rect(10, 40, 200, 30), "lives: " + GameStateManager.getLives());
		GUI.Box(new Rect(10, 70, 200, 30), "time: " + displayTime);
	}
}