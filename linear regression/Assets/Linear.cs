using UnityEngine;
using System.Collections;
using System.Runtime.InteropServices;

public class Linear : MonoBehaviour
{
    
    [DllImport("ConsoleApplication1")]
    static extern public void cleanModel(System.IntPtr model);

    [DllImport("ConsoleApplication1")]
    static extern public System.IntPtr lineaire_model(int nbInput);

    [DllImport("ConsoleApplication1")]
    static extern public double perceptron(double[] value, double[] model, int size);

    [DllImport("ConsoleApplication1")]
    static extern public void regression(System.IntPtr model, double[] inputs, int nbInput, int nbCount, double[] expectedResult);

    [DllImport("ConsoleApplication1")]
    static extern public double classifyRegression(System.IntPtr model, double[] element, int nbInput);

    [SerializeField]
    Transform[] trainingPanel;

    [SerializeField]
    Transform[] panelValues;

    [SerializeField]
    MeshRenderer[] targetRenderer;

    [SerializeField]
    Material red,blue;

    ModelClass configTraining()
    {
        ModelClass training = new ModelClass();
        training.NbElement = panelValues.Length;
        training.inputSize = 2;
        training.TrainingExemples = new double[training.inputSize*training.NbElement];
        training.WaitedValues = new double[training.NbElement];

        for (int i = 0; i < targetRenderer.Length; ++i)
        {
            MeshRenderer renderer = targetRenderer[i].GetComponent<MeshRenderer>();
            if (renderer.material.color == red.color)
            {
                Transform t = panelValues[i].GetComponent<Transform>();
                training.TrainingExemples[i * training.inputSize] = t.position.x;
                training.TrainingExemples[i * training.inputSize + 1] = t.position.z;
                training.WaitedValues[i] = 1;
            }
            if (renderer.material.color == blue.color)
            {
                Transform t = panelValues[i].GetComponent<Transform>();
                training.TrainingExemples[i * training.inputSize] = t.position.x;
                training.TrainingExemples[i * training.inputSize + 1] = t.position.z;
                training.WaitedValues[i] = -1;
            }
        }
        training.size = 10000;
        return training;
    }
    
    void updateView(System.IntPtr model)
    {
        for (int i = 0; i < trainingPanel.Length; i++)
        {
            double[] input = new double[2];
            Transform transform = trainingPanel[i].GetComponent<Transform>();
            MeshRenderer renderer = trainingPanel[i].GetComponent<MeshRenderer>();
            input[0] = transform.position.x;
            input[1] = transform.position.z;
            double colorRatio = classifyRegression(model, input, 2);
            colorRatio = (colorRatio + 1) / 2;

            renderer.material.color = new Color((float)colorRatio, 0f, (float)(1.0 - colorRatio));
        }
    }

    // Use this for initialization
    void Start()
    {
        System.IntPtr model = lineaire_model(configTraining().inputSize + 1);
        var training = configTraining();        
        regression(model, training.TrainingExemples, training.NbElement, training.inputSize, training.WaitedValues);
        updateView(model);
        cleanModel(model);
    }

    // Update is called once per frame
    void Update()
    {

    }

    class ModelClass
    {
        public int NbElement { get; set; }

        public int inputSize { get; set; }

        public double[] TrainingExemples { get; set; }

        public double[] WaitedValues { get; set; }

        public int size { get; set; }
    }
}

