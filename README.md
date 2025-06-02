[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/G8V_0Zaq)

# Tarefa: IoT Security Lab - EmbarcaTech 2025

Autores: **Mauricio Lasca Gonçales e Paulo Santos do Nascimento Filho**

Curso: Residência Tecnológica em Sistemas Embarcados

Instituição: EmbarcaTech - HBr

Campinas, 02 de junho de 2025

---

# Relato e Análise

**Execução das Etapas**

Breve descrição funcionamento:
Este projeto implementa a transmissão de informações entre duas placas BitDogLab utilizando o protocolo MQTT. Ambas as placas se inscrevem no tópico “botãoA/pressionado”, porém apenas uma delas envia mensagens para esse tópico quando o botão A é pressionado. Ao publicar, a placa que enviou a mensagem também a recebe, fazendo com que seu LED azul seja acionado, enquanto a outra placa, que está apenas inscrita, recebe a mesma mensagem e acende seu LED verde. Dessa forma, é demonstrada a comunicação bidirecional em tempo real: quem publica sinaliza sua própria ação com o LED azul e quem apenas escuta confirma o recebimento com o LED verde, garantindo que ambas as BitDogLab permaneçam sincronizadas.
  


https://github.com/user-attachments/assets/fad7013a-32d0-4efa-8700-d604942a3123



Discussão:

• Quais técnicas são escaláveis?
O mecanismo de se inscrever nos tópicos é escalável uma vez que vários dispositivos conseguem se inscrever no mesmo e em diferentes tópicos, como também publicar em cada tópico. Os tópicos podem apresentar restrições de acesso sendo necessário autenticação, isso permite uma melhor gestão em uma rede com diversos dispositivos conectados quando se deseja restringir o acesso a determinados tópicos. Outra tencina é o uso de algum algoritmo de criptografia aumentando a segurança da transmissão.

• Como aplicá-las com várias BitDogLab em rede escolar?
  É possível aplicar esse mecanismo em um ambiente escolar, de modo que uma BitDogLab seja configurada como subscriber enquanto outras placas atuam como publishers, criando um sistema de avisos ou notificações. Nesse cenário, quando uma das placas publicadoras enviar uma mensagem, a BitDogLab inscrita receberá essa informação e poderá emitir um alerta sonoro ou visual para sinalizar a ocorrência. Com essa arquitetura, professores e alunos podem, por exemplo, notificar de forma rápida e eficiente eventos como início de aula, mudança de turno ou aviso de emergência, garantindo uma comunicação imediata e coordenada entre todos os dispositivos conectados.
  
---

## 📜 Licença
GNU GPL-3.0.
