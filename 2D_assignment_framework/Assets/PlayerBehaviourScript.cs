using UnityEngine;
using System.Collections;

public class PlayerBehaviourScript : MonoBehaviour {

	public float speed;
	public float rotationSpeed;
	public float translation;
	public float rotation;
	public float jumpfactor;
	public bool grounded = true;
	public bool fired = false;
	public int direction;
	public Rigidbody2D projectile;
	public Rigidbody2D projectileInst;
	public float projectilespeed;
	public float shootFactorY;
	public Transform onewayplatform;
	public Vector3 SpawnPoint;
	public float timeStamp;
	public float shootCooldown = 7;

	// initialization of variables
	void Start () {
		direction = 1;
		speed = 10.0F;
		rotationSpeed = 50.0F;
		jumpfactor = 11;
		projectile = (Rigidbody2D) Resources.Load("Prefabs/Projectile", typeof(Rigidbody2D));
		projectilespeed = 0.02F * speed;
		shootFactorY = 0.2F;
	}

	// Update is called once per frame
	void Update () {
		// if a, go left
		if (Input.GetKey (KeyCode.A)) {
			direction = -1;
			translation = Input.GetAxis ("Horizontal") * speed;
			translation *= Time.deltaTime;
			transform.Translate(-Vector3.left * translation, transform.parent);
		}

		// if d, go right
		if (Input.GetKey (KeyCode.D)) {
			direction = 1;
			translation = Input.GetAxis ("Horizontal") * speed;
			translation *= Time.deltaTime;
			transform.Translate (Vector3.right * translation, transform.parent);
		}
	
		// if w, jump
		if (Input.GetKey (KeyCode.W) && grounded == true) {
			grounded = false;
			GetComponent<Rigidbody2D>().AddForce(new Vector2(0, jumpfactor), ForceMode2D.Impulse);
		}

		// update "grounded" to correct boolean
		if(grounded == false && GetComponent<Rigidbody2D>().velocity.y == 0) {
			grounded = true;
		}

		// if space bar is pressed, shoot projectile
		if (Input.GetKey(KeyCode.Space) && Time.time >= timeStamp ){
			//Update the shooting cooldown
			timeStamp = Time.time + shootCooldown;

			fired = true;

			// spawning position depends on direction
			Vector2 position;
			position = new Vector2(transform.position.x + direction, transform.position.y);
			// instantiate and shoot projectile
			projectileInst = Instantiate (projectile, position, transform.rotation) as Rigidbody2D;
			projectileInst.AddForce (new Vector2(direction * projectilespeed, shootFactorY * projectilespeed), ForceMode2D.Impulse);
		}

		// method to test restarting of level
		if (transform.position.y < -20){
			GameStateManager.lost ();
		}
	}

	void OnCollisionEnter2D(Collision2D col) {
		if (col.gameObject.tag == "Enemy") {
			GameStateManager.lost ();
		}
		else if (col.gameObject.tag == "Coin") {
			GameStateManager.win ();
		}
	}

	void OnTriggerEnter2D(Collider2D col) {
		if (col.gameObject.tag == "PlatformTrigger") {
			Physics2D.IgnoreCollision (gameObject.GetComponent<BoxCollider2D> (), onewayplatform.GetComponent<Collider2D> ());
		}
	}

	void OnTriggerExit2D() {
		Physics2D.IgnoreCollision (gameObject.GetComponent<BoxCollider2D> (), onewayplatform.GetComponent<Collider2D> (), false);
	}
}