package application.threads;

import application.helper.DataStorage;
import application.helper.ExecuteHelper;
import application.helper.SerializeEstado;
import application.model.ArrivingSocket;
import application.model.Operacao;
import application.model.Snapshot;

import java.io.IOException;
import java.net.DatagramSocket;
import java.net.UnknownHostException;
import java.util.List;
import java.util.logging.Logger;

import static application.helper.DataStorage.getInstance;

public class ThreadProcessSocket extends Thread {

    public static DatagramSocket getServerSocket() {
        return serverSocket;
    }

    private static DatagramSocket serverSocket;
    private static Logger logger = Logger.getLogger(Logger.GLOBAL_LOGGER_NAME);

    public ThreadProcessSocket(DatagramSocket serverSocket) {
        this.serverSocket = serverSocket;
    }

    @Override
    public void run() {

        ThreadSnapshot threadSnapshot = ThreadSnapshot.init();
        Snapshot snapshot = threadSnapshot.getTheMostCurrentSnapshot();
        if(snapshot != null) {
            DataStorage.getInstance().setExecuted(snapshot.getExecuted());
            DataStorage.getInstance().setRegisterHashGrpc(snapshot.getRegisterHashGrpc());
            DataStorage.getInstance().setRegisterHashSocket(snapshot.getRegisterHashSocket());
            DataStorage.getInstance().setArrivingSocket(snapshot.getArrivingSocket());
            DataStorage.getInstance().setArrivingGrpc(snapshot.getArrivingGrpc());

            String message = "System Recovered with version " + snapshot.getVersion();
            System.out.println(message);
        }

        ThreadLogger threadLogger = ThreadLogger.init();
        List<Operacao> operacaos = threadLogger.getLogList();
        if (operacaos != null) {
            for (Operacao operacao : operacaos) {
                ExecuteHelper.executeLogOperation(operacao);
                String message = "EXECUTE:" + "Op:" + operacao.getOperacao()
                        + " Chave: " + operacao.getChave()
                        + " Valor: " + operacao.getValor();
                System.out.println(message);
            }
        }

        while (true) {
            try {
                if (!getInstance().getArrivingSocket().isEmpty()) {
                    String resposta;

                    ArrivingSocket arrivingSocket = getInstance().pollArrivingSocket();
                    Operacao op = SerializeEstado.readOperacao(arrivingSocket.getPackage());
                    op.setGrpc(false);

                    System.out.println(op.toString());

                    if(op.getOperacao()==4) {
                        resposta = getInstance().addRegisterHashSocket(op.getChave(), arrivingSocket.getmPort());
                    }else {
                        resposta = ExecuteHelper.executeOperation(op);
                    }

                    ExecuteHelper.respondClientSocket(serverSocket,
                            resposta.getBytes(),
                            arrivingSocket.getmPort());

                }
            } catch (UnknownHostException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

    }

}
