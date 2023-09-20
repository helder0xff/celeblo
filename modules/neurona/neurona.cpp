#include <iostream>

class Neuron {
private:
    static const uint8_t MAX_NUM_CONEXIONS = 10;
    static const uint8_t MEMBRANE_VOLTAGE_RESET = 0;
    uint8_t     threshold;
    uint8_t     membrane_voltage;
    Neuron*     post_synaptic_neurons[MAX_NUM_CONEXIONS];
    uint8_t     post_synaptic_weights[MAX_NUM_CONEXIONS];
    uint8_t     conection_number;
    uint8_t     id;

    void spike(void){
        std::cout << "Neuron " << int(this->id) << " spiked!" << std::endl;
        for(int i = 0; i < this->conection_number; i++){
            post_synaptic_neurons[i]->get_spike(post_synaptic_weights[i]);
        }
        this->membrane_voltage = 0;        
    }

public:
    Neuron(uint8_t threshold, uint8_t id) : threshold(threshold),
                                            id(id), 
                                            membrane_voltage(0),
                                            conection_number(0) {}

    void get_spike(uint8_t spike_value){
        this->membrane_voltage += spike_value;
        if(this-> threshold <= this->membrane_voltage){
            this->spike();
        }
    }

    void connect(Neuron* post_synaptic_neuron){
        post_synaptic_neurons[conection_number] = post_synaptic_neuron;
        post_synaptic_weights[conection_number] = 32;
        conection_number++;
    }
};

int main() {
    Neuron neuron_1(128, 1);
    Neuron neuron_2(128, 2);
    Neuron neuron_3(64,  3);

    neuron_1.connect(&neuron_2);
    neuron_1.connect(&neuron_3);

    for(int i = 0; i < 1000; i++){
        neuron_1.get_spike(1);
    }


    return 0;
}
