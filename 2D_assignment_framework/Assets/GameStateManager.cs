using UnityEngine;
using System.Collections;


/*
 * Keeps the gamestate throughout the game
 */

public class GameStateManager : MonoBehaviour {

	private static GameStateManager instance = null;
	private static int score = 0;
	private static int lives = 5;
	private static float time;
	private static int level = 1;

	void Start(){
		if (instance != null) {
			GameObject.Destroy (gameObject);
		} else {
			GameObject.DontDestroyOnLoad (gameObject);
			instance = this;
		}
	}

	public static int getScore(){
		return score;
	}

	public static void setScore(int points){
		score += points;
	}

	public static int getLives(){
		return lives;
	}

	public static float getTime(){
		return time;
	}

	public static void setTime(){
		time = Time.time;
	}

	public static int getLevel(){
		return level;
	}

	public static void play(){
		string scene = "Level_" + level;
		UnityEngine.SceneManagement.SceneManager.LoadScene (scene);
	}

	public static void lost(){
		score = 0;
		setTime ();
		lives -= 1;
		UnityEngine.SceneManagement.SceneManager.LoadScene (2);
	}

	public static void win(){
		level += 1;
		UnityEngine.SceneManagement.SceneManager.LoadScene (3);
	}
}