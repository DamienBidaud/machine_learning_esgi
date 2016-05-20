using UnityEngine;
using System.Collections;

public class NewBehaviourScript : MonoBehaviour {

    [SerializeField]
    private Transform targetTransform;

    [SerializeField]
    private Material redMat;

    [SerializeField]
    private Material blueMat;

    [SerializeField]
    private Material greenMat;

    [SerializeField]
    private MeshRenderer targetMeshRenderer;

    // Use this for initialization
    void Start () {
        Debug.Log("Hello");
        targetTransform.position += Vector3.up * 3f;
        targetMeshRenderer.material = blueMat;
	}
	
	// Update is called once per frame
	void Update () {
	
	}
}
