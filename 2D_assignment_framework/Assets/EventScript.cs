using UnityEngine;
using System.Collections;

/*
 * Maintains the UI throughout the game
 */
public class EventScript : MonoBehaviour {

	public int score;
	public int lives;
	public int displayTime;
	public float nextTime;
	public int timeInterval;	
	public float startTime;
	GameStateManager gamestate;

	// Use this for initialization
	void Start () {
		gamestate = GameStateManager.Instance;
		gamestate.setTime ();
		timeInterval = 1;
		startTime = gamestate.getTime ();
		displayTime = (int) (Time.time - startTime);
		nextTime = Time.time + timeInterval;

	}

	void OnGUI(){
		if (gamestate.isGameOver ()) {
			showGameOver ();
		} else {
			// update time every second
			if (Time.time >= nextTime) {
				displayTime = (int)(Time.time - gamestate.getTime ());
				nextTime += timeInterval;
			}
			updateScreen ();
		}
		
	}

	void updateScreen(){
		GUI.Box(new Rect(10, 10, 200, 30), "score: " + gamestate.getScore());
		GUI.Box(new Rect(10, 40, 200, 30), "lives: " + gamestate.getLives());
		GUI.Box(new Rect(10, 70, 200, 30), "time: " + displayTime);
	}

	IEnumerator showGameOver(){
		GUI.Box(new Rect(10, 10, 200, 30), "Game Over");
		yield return new WaitForSeconds (5);
	}

}