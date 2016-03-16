using UnityEngine;
using System.Collections;


/*
 * Singleton - Keeps the gamestate throughout the game
 */

public class GameStateManager {

	private static GameStateManager instance = null;
	private int score;
	private int lives;
	private float time;
	private bool gameOver;

	// intializes a GameState instance
	protected GameStateManager ()
	{
		gameOver = false;
		score = 0;
		lives = 5;
		time = (int) Time.fixedTime;
	}

	// returns singleton GameState instance
	public static GameStateManager Instance {
		get {
			if (GameStateManager.instance == null) {
				GameStateManager.instance = new GameStateManager();
			}
			return GameStateManager.instance;
		}
	}

	public int getScore(){
		return score;
	}

	public int getLives(){
		return lives;
	}

	public void setScore(int points){
		score += points;
	}

	public void setLives(int leftLives){
		lives = leftLives;
	}

	public float getTime(){
		return time;
	}

	public void setTime(){
		time = Time.time;
	}

	public void setGameOver(){
		gameOver = true;
	}

	public void gameNotOver(){
		gameOver = false;
	}

	public bool isGameOver(){
		return gameOver;
	}
}