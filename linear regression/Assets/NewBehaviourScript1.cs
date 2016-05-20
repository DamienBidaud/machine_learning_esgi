using UnityEngine;
using System.Collections;
using System.Runtime.InteropServices;

public class NewBehaviourScript1 : MonoBehaviour {

    [DllImport("ConsoleApplication1")]
    static extern public void createModel(int nbInput, double[] model);

    [DllImport("ConsoleApplication1")]
    static extern public void pal(double[] exemplValue, int size, int inputSize, double[] model, double[] waitValue,
        double coef, int maxIter);

    [DllImport("ConsoleApplication1")]
    static extern public double perceptron(double[] value, double[] model, int size);

    [DllImport("ConsoleApplication1")]
    static extern public double[][] cleanArray(double[] value, int size, int sizeElement);

    [DllImport("ConsoleApplication1")]
    static extern public double lineaire_model(int[] w, int[] x, int sumLength);


    [SerializeField]
    private Transform[] trainingPanel;

    [SerializeField]
    private Transform[] panelValues;


    // Use this for initialization
    void Start () {
        double[] model = new double[2];
        createModel(2, model);

        double[] exemple = new double[trainingPanel.Length * 2];
        int pos = 0;
        int i = 0;
        while (pos < exemple.Length)
        {
            exemple[pos] = trainingPanel[i].position.x;
            exemple[pos + 1] = trainingPanel[i].position.y;
            i++;
            pos = pos + 2;
        }
        double[] waitValues = new double[] { 1, 1, -1, -1 };
        pal(exemple, exemple.Length, 2, model, waitValues, 0.1, 50);
    }
	
	// Update is called once per frame
	void Update () {
	
	}
}
