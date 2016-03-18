using UnityEngine;
using System.Collections;

public class PlayerBehaviourScript : MonoBehaviour {

	public float speed;
	public float translation;
	public float rotation;
	public float jumpfactor;
	public bool grounded = true;
	public int direction;
	public Rigidbody2D projectile;
	public Rigidbody2D projectileInst;
	public float projectilespeed;
	public float shootFactorY;
	public Transform onewayplatform;
	public float timeStamp;
	public float shootCooldown = 0.2F;
	public Sprite left_sprite;
	public Sprite right_sprite;
	public Sprite shooting_sprite;
	public Sprite shooting_sprite_left;

	private SpriteRenderer spriteRenderer; 

	// initialization of variables
	void Start () {
		direction = 1;
		speed = 10.0F;
		jumpfactor = 11;
		projectile = (Rigidbody2D) Resources.Load("Prefabs/Projectile", typeof(Rigidbody2D));
		projectilespeed = 0.01F * speed;
		shootFactorY = 0.1F;
		spriteRenderer = GetComponent<SpriteRenderer>();
	}

	// Update is called once per frame
	void Update () {
		// if a, go left
		if (Input.GetKey (KeyCode.A)) {
			direction = -1;
			translation = Input.GetAxis ("Horizontal") * speed;
			translation *= Time.deltaTime;
			transform.Translate(-Vector3.left * translation, transform.parent);

			//chane side sprite is looking
			if (spriteRenderer.sprite != left_sprite) {
				spriteRenderer.sprite = left_sprite;
			}

		}

		// if d, go right
		if (Input.GetKey (KeyCode.D)) {
			direction = 1;
			translation = Input.GetAxis ("Horizontal") * speed;
			translation *= Time.deltaTime;
			transform.Translate (Vector3.right * translation, transform.parent);

			//change side sprite is looking
			if (spriteRenderer.sprite != right_sprite) {
				spriteRenderer.sprite = right_sprite;
			}
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
			// spawning position depends on direction
			Vector2 position;
			position = new Vector2(transform.position.x + direction, transform.position.y);
			// instantiate and shoot projectile
			projectileInst = Instantiate (projectile, position, transform.rotation) as Rigidbody2D;
			projectileInst.AddForce (new Vector2(direction * projectilespeed, shootFactorY * projectilespeed), ForceMode2D.Impulse);


			//change side sprite to shooting position
			if (spriteRenderer.sprite == right_sprite) {
				spriteRenderer.sprite = shooting_sprite;
			}

			else if (spriteRenderer.sprite == left_sprite) {
					spriteRenderer.sprite = shooting_sprite_left;
				}
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
		if (onewayplatform) {
			Physics2D.IgnoreCollision (gameObject.GetComponent<BoxCollider2D> (), onewayplatform.GetComponent<Collider2D> (), false);
		}
	}
}