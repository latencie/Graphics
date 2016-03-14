using UnityEngine;
using System.Collections;

public class PlayerBehaviourScript : MonoBehaviour {

	public float speed;
	public float rotationSpeed;
	public float translation;
	public float rotation;
	public int jumpfactor;
	public bool grounded = true;
	public Component camera;

	// Use this for initialization
	void Start () {
		speed = 10.0F;
		rotationSpeed = 50.0F;
		jumpfactor = 1;
	}

	// Update is called once per frame
	void Update () {

		// if a, go left
		if (Input.GetKey (KeyCode.A)) {
			translation = Input.GetAxis("Horizontal") * speed;
			translation *= Time.deltaTime;
			transform.Translate(-Vector3.left * translation);
			camera.transform.Translate(-Vector3.left * translation);
		}

		// if d, go right
		if (Input.GetKey (KeyCode.D)) {
			translation = Input.GetAxis ("Horizontal") * speed;
			translation *= Time.deltaTime;
			transform.Translate (Vector3.right * translation);
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
	}
}