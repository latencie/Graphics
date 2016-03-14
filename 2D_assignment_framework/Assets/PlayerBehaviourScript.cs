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

	// Use this for initialization
	void Start () {
		direction = 1;
		speed = 10.0F;
		rotationSpeed = 50.0F;
		jumpfactor = 1;
		projectile = (Rigidbody2D) UnityEditor.AssetDatabase.LoadAssetAtPath("Assets/Prefabs/Projectile.prefab", typeof(Rigidbody2D));
	}

	// Update is called once per frame
	void Update () {

		// if a, go left
		if (Input.GetKey (KeyCode.A)) {
			direction = -1;
			translation = Input.GetAxis("Horizontal") * speed;
			translation *= Time.deltaTime;
			transform.Translate(-Vector3.left * translation, transform.parent);
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
			GetComponent<Rigidbody2D>().AddForce(new Vector2(0,12), ForceMode2D.Impulse);
		}

		if(grounded == false && GetComponent<Rigidbody2D>().velocity.y == 0) {
			grounded = true;
		}

		// if space bar is pressed, shoot projectile
		if (Input.GetKey(KeyCode.Space) && fired == false){
			fired = true;
			Vector2 position;
			if (transform.rotation == new Quaternion(0.0F, 0.0F, 1.0F, 0.0F)){
				position = new Vector2(transform.position.x + (direction + 1) * 0.5F, transform.position.y);
			}
			else {position = new Vector2(transform.position.x + (direction - 1) * 0.5F, transform.position.y);}
			projectileInst = Instantiate (projectile, position, transform.rotation) as Rigidbody2D;
			projectileInst.AddForce (new Vector2(direction * 0.05F * speed, 0), ForceMode2D.Impulse);
		}

		if (Input.GetKey (KeyCode.RightShift)) {
			Destroy(projectileInst);
		}

		if(fired == true && !projectileInst) {
			fired = false;
		}
	}
}