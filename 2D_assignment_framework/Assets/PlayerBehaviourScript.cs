using UnityEngine;
using System.Collections;

public class PlayerBehaviourScript : MonoBehaviour {

	public float speed;
	public float rotationSpeed;
	public float translation;
	public float rotation;
	public int jumpfactor;

	// Use this for initialization
	void Start () {
		speed = 10.0F;
		rotationSpeed = 50.0F;
		jumpfactor = 2;
	}

	// Update is called once per frame
	void Update () {

		// if a, go left
		if (Input.GetKey (KeyCode.A)) {
			translation = Input.GetAxis("Horizontal") * speed;
			translation *= Time.deltaTime;
			transform.Translate(-Vector3.left * translation);
		}

		// if d, go right
		if (Input.GetKey (KeyCode.D)) {
			translation = Input.GetAxis ("Horizontal") * speed;
			translation *= Time.deltaTime;
			transform.Translate (Vector3.right * translation);
		}

		// if w, jump
		if (Input.GetKey (KeyCode.W)) {
			translation = Input.GetAxis ("Vertical") * jumpfactor * speed;
			translation *= Time.deltaTime;
			transform.Translate (Vector3.up * translation);
		}
	}
}
