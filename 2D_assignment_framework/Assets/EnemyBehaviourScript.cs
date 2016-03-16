﻿using UnityEngine;
using System.Collections;

public class EnemyBehaviourScript : MonoBehaviour {

	public float speed;
	public float rotationSpeed;
	public float translation;
	public float rotation;
	public int direction;
	public string move_dir = "left";
	Vector3 walkAmount;
	public Collider2D move_trigger;
	public GameStateManager gamestate;

	// initialization of variables
	void Start () {
		direction = 1;
		speed = 2.0F;
		rotationSpeed = 50.0F;
		gamestate = GameStateManager.Instance;
	}

	// Update is called once per frame
	void Update () {
		if (move_dir == "left") {
			direction = -1;
			walkAmount.x = direction * speed * Time.deltaTime;
			transform.Translate(walkAmount);
		}

		// if d, go right
		if (move_dir == "right") {
			direction = 1;
			walkAmount.x = direction * speed * Time.deltaTime;
			transform.Translate(walkAmount);
		}

	}

	void OnTriggerEnter2D(Collider2D move_trigger) {
		if (move_dir == "right") {
			move_dir = "left";
		} else {
			move_dir = "right";
		}
	}


	void OnCollisionEnter2D(Collision2D collision){
		if (collision.collider.gameObject.name == "Projectile(Clone)"){
			Destroy (gameObject);
			gamestate.setScore (5);
		} 
	}
}