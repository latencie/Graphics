using UnityEngine;
using System.Collections;

public class ProjectileBehaviourScript : MonoBehaviour {

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}

	void OnCollisionEnter2D(Collision collision) {
		Destroy(gameObject);
	}

	void OnBecameInvisible(){
		Destroy(gameObject);
	}
}
