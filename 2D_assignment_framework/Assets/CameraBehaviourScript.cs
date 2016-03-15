using UnityEngine;
using System.Collections;

public class CameraBehaviourScript : MonoBehaviour {

	public GameObject player;

	// Use this for initialization
	void Start () {
	
	}

	void Update() {
		if (GameObject.Find ("Player")) {
			transform.position = new Vector3 (GameObject.Find ("Player").transform.position.x, GameObject.Find ("Player").transform.position.y, 
				transform.position.z);
		}
	}
}
