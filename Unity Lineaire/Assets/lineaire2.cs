using UnityEngine;
using System.Collections;
using System.Runtime.InteropServices;

public class lineaire2 : MonoBehaviour {

    [DllImport("cygmachine_learning")]
    static extern public void createModel(int nbInput, double[] model);

    [DllImport("cygmachine_learning")]
    static extern public void pal(double[] exemplValue, int size, int inputSize, double[] model, double[] waitValue,
        double coef, int maxIter);

    [DllImport("cygmachine_learning")]
    static extern public double perceptron(double[] value, double[] model, int size);

    [DllImport("cygmachine_learning")]
    static extern public void regresion(double[] valueSend, int size, int inputSize, double[] waitValue, double[] model);


    [SerializeField]
    private Transform[] trainingPanel;

    [SerializeField]
    private Transform[] panelValues;

    [SerializeField]
    private MeshRenderer[] targeRenderer;
    // Use this for initialization
    void Start()
    {
        double[] model = new double[2];
        createModel(2, model);

        Debug.Log(model[0]);
        Debug.Log(model[1]);
        double[] exemple = new double[trainingPanel.Length * 2];
        int pos = 0;
        int i = 0;
        while (pos < exemple.Length)
        {
            exemple[pos] = trainingPanel[i].position.x;
            exemple[pos + 1] = trainingPanel[i].position.z;
            i++;
            pos = pos + 2;
        }
        double[] waitValues = new double[] {
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            1,
            1,
            1,
            1,
            1,
            1,
            1,
            1,
            1,
            1,
            1,
            1,
            1,
            1,
            1,
            1,
            1,
            1,
            1,
            1,
            1,
            1,
            1,
            1,
            1 };
        pal(exemple, exemple.Length, 2, model, waitValues, 0.1, 5000);
        Debug.Log(model[0]);
        Debug.Log(model[1]);
        for (i = 0; i < panelValues.Length; i++)
        {
            if (perceptron(new double[] { panelValues[i].position.x, panelValues[i].position.z }, model, 2) < 0)
            {
                targeRenderer[i].material.color = Color.blue;
            }
            else
            {
                targeRenderer[i].material.color = Color.red;
            }
        }
    }

    // Update is called once per frame
    void Update () {
	
	}
}
