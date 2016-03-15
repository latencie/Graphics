using UnityEngine;
using System.Collections;

public class PlayerBehaviourScript : MonoBehaviour {

	public float speed;
	public float rotationSpeed;
	public float translation;
	public float rotation;
	public int jumpfactor;
	public bool grounded = true;
	public bool fired = false;
	public int direction;
	public Component camera;
	public Rigidbody2D projectile;
	public Rigidbody2D projectileInst;
	public float projectilespeed;
	public float shootFactorY;

	// initialization of variables
	void Start () {
		direction = 1;
		speed = 10.0F;
		rotationSpeed = 50.0F;
		jumpfactor = 12;
		projectile = (Rigidbody2D) UnityEditor.AssetDatabase.LoadAssetAtPath("Assets/Prefabs/Projectile.prefab", typeof(Rigidbody2D));
		projectilespeed = 0.03F * speed;
		shootFactorY = 0.2F;
	}

	// Update is called once per frame
	void Update () {

		// if a, go left
		if (Input.GetKey (KeyCode.A)) {
<<<<<<< HEAD
			translation = Input.GetAxis("Horizontal") * speed * Time.deltaTime;
			transform.Translate(-Vector3.left * translation);
=======
			direction = -1;
			translation = Input.GetAxis("Horizontal") * speed;
			translation *= Time.deltaTime;
			transform.Translate(-Vector3.left * translation, transform.parent);
>>>>>>> 3acf427ec758c93004850304b7c8596e5ed3ad92
			camera.transform.Translate(-Vector3.left * translation);
		}

		// if d, go right
		if (Input.GetKey (KeyCode.D)) {
			direction = 1;
			translation = Input.GetAxis ("Horizontal") * speed;
			translation *= Time.deltaTime;
			transform.Translate (Vector3.right * translation, transform.parent);
			camera.transform.Translate(Vector3.right * translation);
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
		if (Input.GetKey(KeyCode.Space) && fired == false){
			fired = true;
			// spawning position depends on direction
			Vector2 position;
			position = new Vector2(transform.position.x + direction, transform.position.y);
			// instantiate and shoot projectile
			projectileInst = Instantiate (projectile, position, transform.rotation) as Rigidbody2D;
			projectileInst.AddForce (new Vector2(direction * projectilespeed, shootFactorY * projectilespeed), ForceMode2D.Impulse);
		}

		// update "fired" to correct boolean 
		if(fired == true && !projectileInst) {
			fired = false;
		}
	}
}